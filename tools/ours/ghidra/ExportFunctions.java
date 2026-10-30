// ExportFunctions.java -- headless Ghidra postScript: dump program metadata, every function and
// listing statistics as JSON. Read-only; never writes to the program.
//
//   analyzeHeadless <projdir> p3fes -process SLUS_216.21 -noanalysis -readOnly \
//       -scriptPath tools/ours/ghidra -postScript ExportFunctions.java <out.json>
//
// Dependency-free (java.* + ghidra.* only) so headless can compile it on the fly.
// Consumer: tools/ours/ghidra/diff_functions.py (IDA vs Ghidra boundary diff).
//@category P3FES
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressRangeIterator;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.MemoryBlock;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.Writer;

public class ExportFunctions extends GhidraScript {

    private static String q(String s) {
        if (s == null) return "null";
        StringBuilder b = new StringBuilder("\"");
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            switch (c) {
                case '"': b.append("\\\""); break;
                case '\\': b.append("\\\\"); break;
                case '\n': b.append("\\n"); break;
                case '\r': b.append("\\r"); break;
                case '\t': b.append("\\t"); break;
                default:
                    if (c < 0x20) b.append(String.format("\\u%04x", (int) c));
                    else b.append(c);
            }
        }
        return b.append('"').toString();
    }

    private static String hex(Address a) {
        return "0x" + Long.toHexString(a.getOffset());
    }

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 1) {
            printerr("usage: ExportFunctions.java <out.json>");
            return;
        }
        Listing listing = currentProgram.getListing();
        try (Writer w = new BufferedWriter(new FileWriter(args[0]))) {
            w.write("{\n");
            w.write(" \"program\": {\n");
            w.write("  \"name\": " + q(currentProgram.getName()) + ",\n");
            w.write("  \"executable_path\": " + q(currentProgram.getExecutablePath()) + ",\n");
            w.write("  \"executable_md5\": " + q(currentProgram.getExecutableMD5()) + ",\n");
            w.write("  \"executable_sha256\": " + q(currentProgram.getExecutableSHA256()) + ",\n");
            w.write("  \"format\": " + q(currentProgram.getExecutableFormat()) + ",\n");
            w.write("  \"language_id\": " + q(currentProgram.getLanguageID().getIdAsString()) + ",\n");
            w.write("  \"processor\": " + q(currentProgram.getLanguage().getProcessor().toString()) + ",\n");
            w.write("  \"language_version\": " + q(currentProgram.getLanguage().getVersion() + "." + currentProgram.getLanguage().getMinorVersion()) + ",\n");
            w.write("  \"compiler_spec\": " + q(currentProgram.getCompilerSpec().getCompilerSpecID().getIdAsString()) + ",\n");
            w.write("  \"compiler\": " + q(currentProgram.getCompiler()) + ",\n");
            w.write("  \"image_base\": " + q(hex(currentProgram.getImageBase())) + ",\n");
            w.write("  \"ghidra_version\": " + q(ghidra.framework.Application.getApplicationVersion()) + ",\n");
            w.write("  \"memory_blocks\": [\n");
            MemoryBlock[] blocks = currentProgram.getMemory().getBlocks();
            for (int i = 0; i < blocks.length; i++) {
                MemoryBlock b = blocks[i];
                String perms = (b.isRead() ? "r" : "-") + (b.isWrite() ? "w" : "-") + (b.isExecute() ? "x" : "-");
                w.write("   {\"name\": " + q(b.getName()) + ", \"start\": " + q(hex(b.getStart()))
                        + ", \"end\": " + q(hex(b.getEnd())) + ", \"size\": " + b.getSize()
                        + ", \"perms\": " + q(perms) + ", \"initialized\": " + b.isInitialized()
                        + ", \"type\": " + q(b.getType().toString())
                        + ", \"overlay\": " + b.isOverlay()
                        + ", \"source\": " + q(b.getSourceName()) + "}" + (i + 1 < blocks.length ? "," : "") + "\n");
            }
            w.write("  ]\n },\n");

            // Listing statistics.
            long instr = listing.getNumInstructions();
            long data = listing.getNumDefinedData();
            MemoryBlock main = currentProgram.getMemory().getBlock("main");
            if (main == null) main = currentProgram.getMemory().getBlock(currentProgram.getImageBase());
            long undefMain = -1;
            String mainName = null;
            if (main != null) {
                mainName = main.getName();
                undefMain = 0;
                AddressSetView mainSet = new AddressSet(main.getStart(), main.getEnd());
                AddressRangeIterator it = listing.getUndefinedRanges(mainSet, false, monitor).getAddressRanges();
                while (it.hasNext()) {
                    AddressRange r = it.next();
                    undefMain += r.getLength();
                }
            }
            int fnCount = currentProgram.getFunctionManager().getFunctionCount();
            w.write(" \"stats\": {\n");
            w.write("  \"functions\": " + fnCount + ",\n");
            w.write("  \"instructions\": " + instr + ",\n");
            w.write("  \"defined_data\": " + data + ",\n");
            w.write("  \"main_block\": " + q(mainName) + ",\n");
            w.write("  \"undefined_bytes_in_main\": " + undefMain + "\n");
            w.write(" },\n");

            // Functions.
            w.write(" \"functions\": [\n");
            FunctionIterator fi = listing.getFunctions(true);
            boolean first = true;
            long totalBytes = 0;
            while (fi.hasNext() && !monitor.isCancelled()) {
                Function f = fi.next();
                AddressSetView body = f.getBody();
                long size = 0;
                int ranges = 0;
                AddressRangeIterator ri = body.getAddressRanges();
                while (ri.hasNext()) {
                    size += ri.next().getLength();
                    ranges++;
                }
                totalBytes += size;
                String cc = f.getCallingConventionName();
                String sig;
                try {
                    sig = f.getPrototypeString(false, false);
                } catch (Exception e) {
                    sig = "<error: " + e.getMessage() + ">";
                }
                Address end = body.getMaxAddress();
                if (!first) w.write(",\n");
                first = false;
                w.write("  {\"a\": " + q(hex(f.getEntryPoint())) + ", \"s\": " + size + ", \"ranges\": " + ranges
                        + ", \"end\": " + q(end == null ? "" : hex(end))
                        + ", \"n\": " + q(f.getName()) + ", \"thunk\": " + f.isThunk()
                        + ", \"cc\": " + q(cc) + ", \"sig\": " + q(sig)
                        + ", \"noreturn\": " + f.hasNoReturn()
                        + ", \"params\": " + f.getParameterCount()
                        + ", \"src\": " + q(f.getSymbol().getSource().toString()) + "}");
            }
            w.write("\n ],\n");
            w.write(" \"total_function_bytes\": " + totalBytes + "\n");
            w.write("}\n");
        }
        println("ExportFunctions: wrote " + args[0] + " (" + currentProgram.getFunctionManager().getFunctionCount() + " functions)");
    }
}
