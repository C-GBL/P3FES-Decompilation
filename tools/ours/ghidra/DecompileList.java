// DecompileList.java -- headless Ghidra postScript: decompile a list of functions with the
// EE extension's decompiler and save each as <outdir>/<addr>.c. Read-only.
//
//   analyzeHeadless <projdir> p3fes -process SLUS_216.21 -noanalysis -readOnly \
//       -scriptPath tools/ours/ghidra -postScript DecompileList.java <addrs.txt> <outdir>
//
// <addrs.txt>: one hex address per line (0x prefix optional, '#' comments allowed).
// Each output file begins with a header comment recording the function name, body,
// decompile status and error message, so failures are preserved verbatim.
//@category P3FES
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.Writer;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;

public class DecompileList extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) {
            printerr("usage: DecompileList.java <addrs.txt> <outdir>");
            return;
        }
        List<String> lines = Files.readAllLines(new File(args[0]).toPath());
        File outDir = new File(args[1]);
        outDir.mkdirs();

        DecompInterface decomp = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        decomp.setOptions(opts);
        decomp.toggleCCode(true);
        decomp.toggleSyntaxTree(true);
        decomp.setSimplificationStyle("decompile");
        if (!decomp.openProgram(currentProgram)) {
            printerr("DecompileList: openProgram failed: " + decomp.getLastMessage());
            return;
        }
        List<String> summary = new ArrayList<>();
        try {
            for (String raw : lines) {
                String s = raw.trim();
                int hash = s.indexOf('#');
                if (hash >= 0) s = s.substring(0, hash).trim();
                if (s.isEmpty()) continue;
                String hexs = s.toLowerCase().startsWith("0x") ? s.substring(2) : s;
                long off = Long.parseLong(hexs, 16);
                Address addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(off);
                String tag = String.format("%08x", off);
                File out = new File(outDir, tag + ".c");
                Function f = getFunctionAt(addr);
                Function containing = f == null ? getFunctionContaining(addr) : null;
                int warn = 0;
                try (Writer w = new BufferedWriter(new FileWriter(out))) {
                    w.write("// DecompileList: request 0x" + tag + "\n");
                    if (f == null) {
                        w.write("// STATUS: no function starts here");
                        if (containing != null) {
                            w.write("; containing function " + containing.getName() + " @ 0x"
                                    + Long.toHexString(containing.getEntryPoint().getOffset()));
                        }
                        w.write("\n");
                        summary.add(tag + " NOFUNC" + (containing != null ? " (inside " + containing.getName() + ")" : ""));
                        continue;
                    }
                    w.write("// function: " + f.getName() + "  entry 0x" + Long.toHexString(f.getEntryPoint().getOffset())
                            + "  body_bytes " + f.getBody().getNumAddresses()
                            + "  ranges " + f.getBody().getNumAddressRanges()
                            + "  cc " + f.getCallingConventionName() + "\n");
                    monitor.setMessage("decompile " + f.getName());
                    long t0 = System.currentTimeMillis();
                    DecompileResults res = decomp.decompileFunction(f, 120, monitor);
                    long ms = System.currentTimeMillis() - t0;
                    boolean ok = res != null && res.decompileCompleted();
                    String err = res == null ? "null result" : res.getErrorMessage();
                    w.write("// STATUS: " + (ok ? "completed" : "FAILED") + "  (" + ms + " ms)\n");
                    if (err != null && !err.trim().isEmpty()) {
                        w.write("// ERROR: " + err.trim().replace("\n", "\n// ERROR: ") + "\n");
                    }
                    String c = null;
                    if (res != null && res.getDecompiledFunction() != null) {
                        c = res.getDecompiledFunction().getC();
                    }
                    if (c != null) {
                        for (String l : c.split("\n")) if (l.contains("WARNING")) warn++;
                        w.write("// C lines: " + c.split("\n").length + "  WARNING lines: " + warn + "\n\n");
                        w.write(c);
                    } else {
                        w.write("// (no C output)\n");
                    }
                    summary.add(tag + " " + f.getName() + " " + (ok ? "ok" : "FAILED") + " " + ms + "ms warn=" + warn
                            + (err != null && !err.trim().isEmpty() ? " err=" + err.trim().split("\n")[0] : ""));
                }
            }
        } finally {
            decomp.dispose();
        }
        for (String s : summary) println("DecompileList: " + s);
    }
}
