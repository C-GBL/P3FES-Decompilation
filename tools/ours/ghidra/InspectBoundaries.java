// InspectBoundaries.java -- headless Ghidra postScript: explain boundary disagreements.
// For each address in <addrs.txt>, print the Ghidra function (if any) at/containing it, its body
// ranges, the last instruction of every range with its flow type, callees flagged no-return, the
// instruction/data defined at the address itself, and references to it. Read-only.
//
//   analyzeHeadless <projdir> p3fes -process SLUS_216.21 -noanalysis -readOnly \
//       -scriptPath tools/ours/ghidra -postScript InspectBoundaries.java <addrs.txt> <out.txt>
//@category P3FES
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressRangeIterator;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.Writer;
import java.nio.file.Files;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class InspectBoundaries extends GhidraScript {

    private static String hx(Address a) {
        return a == null ? "null" : "0x" + Long.toHexString(a.getOffset());
    }

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) {
            printerr("usage: InspectBoundaries.java <addrs.txt> <out.txt>");
            return;
        }
        List<String> lines = Files.readAllLines(new File(args[0]).toPath());
        try (Writer w = new BufferedWriter(new FileWriter(args[1]))) {
            for (String raw : lines) {
                String s = raw.trim();
                int hash = s.indexOf('#');
                if (hash >= 0) s = s.substring(0, hash).trim();
                if (s.isEmpty()) continue;
                String hexs = s.toLowerCase().startsWith("0x") ? s.substring(2) : s;
                Address addr = toAddr(Long.parseLong(hexs, 16));
                w.write("=== " + hx(addr) + "\n");
                CodeUnit cu = currentProgram.getListing().getCodeUnitContaining(addr);
                if (cu == null) {
                    w.write("  code unit: none (undefined)\n");
                } else if (cu instanceof Instruction) {
                    w.write("  code unit: instruction @" + hx(cu.getMinAddress()) + "  " + cu.toString() + "\n");
                } else {
                    w.write("  code unit: data @" + hx(cu.getMinAddress()) + "  " + cu.toString() + "\n");
                }
                int nrefs = 0;
                StringBuilder refs = new StringBuilder();
                ReferenceIterator ri = currentProgram.getReferenceManager().getReferencesTo(addr);
                while (ri.hasNext()) {
                    Reference r = ri.next();
                    if (nrefs < 6) {
                        Function ff = getFunctionContaining(r.getFromAddress());
                        refs.append(" ").append(hx(r.getFromAddress())).append("(").append(r.getReferenceType())
                            .append(ff == null ? "" : "," + ff.getName()).append(")");
                    }
                    nrefs++;
                }
                w.write("  refs to: " + nrefs + refs + "\n");
                Function f = getFunctionAt(addr);
                Function c = getFunctionContaining(addr);
                if (f == null && c != null) {
                    w.write("  inside function " + c.getName() + " @" + hx(c.getEntryPoint()) + "\n");
                }
                Function g = f != null ? f : c;
                if (g == null) {
                    w.write("  no Ghidra function\n");
                    continue;
                }
                w.write("  function " + g.getName() + " entry " + hx(g.getEntryPoint()) + " body " + g.getBody().getNumAddresses()
                        + " bytes, ranges " + g.getBody().getNumAddressRanges() + ", noreturn=" + g.hasNoReturn()
                        + ", thunk=" + g.isThunk() + "\n");
                AddressRangeIterator ari = g.getBody().getAddressRanges();
                while (ari.hasNext()) {
                    AddressRange r = ari.next();
                    Instruction last = currentProgram.getListing().getInstructionContaining(r.getMaxAddress());
                    Instruction prev = last == null ? null : last.getPrevious();
                    w.write("   range " + hx(r.getMinAddress()) + ".." + hx(r.getMaxAddress()) + " (" + r.getLength() + ")"
                            + "  last: " + (last == null ? "<no instr>" : hx(last.getMinAddress()) + " " + last + " flow=" + last.getFlowType())
                            + (prev == null ? "" : "  prev: " + prev)
                            + "\n");
                    // What lies right after the range?
                    Address after = r.getMaxAddress().add(1);
                    CodeUnit ncu = currentProgram.getListing().getCodeUnitAt(after);
                    Function nf = getFunctionContaining(after);
                    w.write("     after: " + (ncu == null ? "undefined" : (ncu instanceof Instruction ? "instr " : "data ") + ncu)
                            + (nf == null ? "  (no function)" : "  in " + nf.getName() + " @" + hx(nf.getEntryPoint())) + "\n");
                }
                // Undefined words inside the function's span (gaps between body ranges): dump the raw
                // 32-bit LE word so the opcode class can be decoded by hand (first 40 gaps).
                if (g.getBody().getNumAddressRanges() > 1) {
                    Address lo = g.getBody().getMinAddress(), hi = g.getBody().getMaxAddress();
                    int shown = 0;
                    for (Address p = lo; p.compareTo(hi) < 0 && shown < 40; p = p.add(4)) {
                        if (g.getBody().contains(p)) continue;
                        CodeUnit gcu = currentProgram.getListing().getCodeUnitAt(p);
                        String kind = gcu == null ? "undefined" : (gcu instanceof Instruction ? "instr(other fn?) " + gcu : "data " + gcu.getMnemonicString());
                        String word;
                        try {
                            word = String.format("0x%08x", currentProgram.getMemory().getInt(p));
                        } catch (Exception e) {
                            word = "<unreadable>";
                        }
                        w.write("     gap " + hx(p) + " word=" + word + " " + kind + "\n");
                        shown++;
                    }
                }
                Set<Function> called = g.getCalledFunctions(monitor);
                Set<String> nr = new HashSet<>();
                for (Function cf : called) if (cf.hasNoReturn()) nr.add(cf.getName() + "@" + hx(cf.getEntryPoint()));
                w.write("  callees " + called.size() + ", no-return callees: " + nr + "\n");
            }
        }
        println("InspectBoundaries: wrote " + args[1]);
    }
}
