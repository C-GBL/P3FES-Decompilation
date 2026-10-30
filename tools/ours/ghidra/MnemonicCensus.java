// MnemonicCensus.java -- headless Ghidra postScript: for each function in <addrs.txt>, count
// instruction mnemonics inside its body and report, per mnemonic, how the SLEIGH lifts it:
// number of p-code ops and whether any is CALLOTHER (= opaque intrinsic for the decompiler).
// This decides "lifted vs intrinsic" for MMI/COP2 ops independently of decompiler output. Read-only.
//
//   analyzeHeadless <projdir> p3fes -process SLUS_216.21 -noanalysis -readOnly \
//       -scriptPath tools/ours/ghidra -postScript MnemonicCensus.java <addrs.txt> <out.txt>
//@category P3FES
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.pcode.PcodeOp;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.Writer;
import java.nio.file.Files;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class MnemonicCensus extends GhidraScript {

    private static final class Stat {
        int count;
        int pcodeOps;
        int callother;
        String example;
    }

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) {
            printerr("usage: MnemonicCensus.java <addrs.txt> <out.txt>");
            return;
        }
        List<String> lines = Files.readAllLines(new File(args[0]).toPath());
        Map<String, Stat> global = new TreeMap<>();
        try (Writer w = new BufferedWriter(new FileWriter(args[1]))) {
            for (String raw : lines) {
                String s = raw.trim();
                int hash = s.indexOf('#');
                if (hash >= 0) s = s.substring(0, hash).trim();
                if (s.isEmpty()) continue;
                String hexs = s.toLowerCase().startsWith("0x") ? s.substring(2) : s;
                Address addr = toAddr(Long.parseLong(hexs, 16));
                Function f = getFunctionAt(addr);
                if (f == null) {
                    w.write("=== 0x" + Long.toHexString(addr.getOffset()) + ": no function\n");
                    continue;
                }
                Map<String, Stat> local = new TreeMap<>();
                int total = 0;
                InstructionIterator ii = currentProgram.getListing().getInstructions(f.getBody(), true);
                while (ii.hasNext()) {
                    Instruction in = ii.next();
                    total++;
                    String m = in.getMnemonicString();
                    PcodeOp[] ops = in.getPcode();
                    int co = 0;
                    for (PcodeOp op : ops) if (op.getOpcode() == PcodeOp.CALLOTHER) co++;
                    for (Map<String, Stat> mp : new Map[] { local, global }) {
                        Stat st = mp.computeIfAbsent(m, k -> new Stat());
                        st.count++;
                        st.pcodeOps += ops.length;
                        st.callother += co;
                        if (st.example == null) st.example = "0x" + Long.toHexString(in.getMinAddress().getOffset()) + " " + in;
                    }
                }
                w.write("=== 0x" + Long.toHexString(addr.getOffset()) + " " + f.getName() + " instructions=" + total
                        + " body=" + f.getBody().getNumAddresses() + "\n");
                for (Map.Entry<String, Stat> e : local.entrySet()) {
                    Stat st = e.getValue();
                    boolean interesting = st.callother > 0 || e.getKey().startsWith("p") || e.getKey().equals("lq")
                            || e.getKey().equals("sq") || e.getKey().contains("c2") || e.getKey().startsWith("v")
                            || e.getKey().startsWith("mt") || e.getKey().startsWith("mf") || e.getKey().equals("syscall")
                            || e.getKey().startsWith("q") || e.getKey().startsWith("mult") || e.getKey().startsWith("madd")
                            || e.getKey().startsWith("div") || e.getKey().startsWith("plzcw") || e.getKey().startsWith("mfsa");
                    if (!interesting) continue;
                    w.write(String.format("  %-10s n=%-4d pcode/insn=%.1f callother=%d  e.g. %s\n", e.getKey(), st.count,
                            st.pcodeOps / (double) st.count, st.callother, st.example));
                }
            }
            w.write("=== GLOBAL (all listed functions): mnemonics whose p-code contains CALLOTHER\n");
            for (Map.Entry<String, Stat> e : global.entrySet()) {
                Stat st = e.getValue();
                if (st.callother > 0)
                    w.write(String.format("  %-10s n=%-4d callother=%d  e.g. %s\n", e.getKey(), st.count, st.callother, st.example));
            }
            w.write("=== GLOBAL: mnemonics starting with p/q or lq/sq lifted WITHOUT CALLOTHER\n");
            for (Map.Entry<String, Stat> e : global.entrySet()) {
                Stat st = e.getValue();
                String k = e.getKey();
                if (st.callother == 0 && (k.startsWith("p") || k.startsWith("q") || k.equals("lq") || k.equals("sq")))
                    w.write(String.format("  %-10s n=%-4d pcode/insn=%.1f  e.g. %s\n", k, st.count, st.pcodeOps / (double) st.count, st.example));
            }
        }
        println("MnemonicCensus: wrote " + args[1]);
    }
}
