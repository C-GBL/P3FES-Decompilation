/* Phase 2 topic 12 types (docs/ANALYSIS/12_irx_rpc_threads.md). Re-parse with ida_typeinf.parse_decls; apply with irx_rpc_threads.apply.txt. */
typedef unsigned int u32; typedef int s32; typedef unsigned short u16; typedef short s16; typedef unsigned char u8;
/* libkernel kernel-patch table entry: SetSyscall(syscall_no, handler) or (syscall_no, GetEntryAddress(syscall_no)) when handler==0 */
struct KPatchEntry { s32 syscall_no; u32 handler; };
/* SCE ThreadParam (CreateThread); option carries the thread-name string pointer in this SDK */
struct SceThreadParam { s32 status; u32 entry; u32 stack; s32 stackSize; u32 gpReg; s32 initPriority; s32 currentPriority; u32 attr; u32 option; s32 waitType; s32 waitId; s32 wakeupCount; };
/* SCE SemaParam (CreateSema); option = name string pointer */
struct SceSemaParam { s32 currentCount; s32 maxCount; s32 initCount; s32 numWaitThreads; u32 attr; u32 option; };
/* sifrpc client descriptor (sceSifBindRpc/sceSifCallRpc) */
struct SceSifRpcClientData { u32 pkt_addr; u32 rpc_id; s32 sema_id; u32 mode; u32 command; u32 buff; u32 cbuff; u32 end_function; u32 end_param; u32 server; };
/* sceSifSetDma element */
struct SceSifDmaData { u32 data; u32 addr; u32 size; u32 mode; };
/* loadfile RPC 0x80000006 cmd 0 request/response (512 bytes) */
struct LfModuleLoadArg { s32 arg_len_or_result; s32 modres; char path[252]; char args[252]; };
/* libpad RPC 0x80000100 cmd 1 buffer (128 bytes): func 16 Init,15 End,1 PortOpen,14 PortClose,6 SetMainMode,8 SetActAlign,10 SetButtonInfo,11 SetVrefParam,12 GetPortMax,13 GetSlotMax,18 GetModVersion,20 SetWarningLevel,24 SetDmaCallback */
struct PadRpcBuf { s32 func; s32 port; s32 slot; s32 param0; s32 param1; s32 rest[27]; };
/* libsdr sceSdRemote argument/result block (64 bytes): self pointer then up to 6 args; reply (16 bytes) overwrites the start */
struct SdrRemoteArgBlock { u32 self; s32 arg[6]; s32 pad[9]; };
/* libsk command block sent through sceSdRemote(1,0x9100,blk,64): module 0=SOUND,0x1000000=HSYNTH,0x4000000=SESQ */
struct SkCmdBlock { u32 module; u32 func; s32 arg[14]; };
/* H_Sndcom bank slot (17 words, 6 slots at sSndcomWork) */
struct HSndcomSlot { s16 state; s16 pad0; s32 cdvdReq; s16 pad1; s16 bankIdx; s32 hsynId; s32 hsynId2; s32 sesqId; s32 bound; u32 iopHd; s32 hdSize; u32 spuAddr; s32 bdSize; u32 iopSq; s32 sqSize; u32 srcHd; u32 srcBd; u32 srcSq; s32 ctl; };
