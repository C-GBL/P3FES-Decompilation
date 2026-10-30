/* symbols/types/file_io.h - types recovered in Phase 2 topic 11 (docs/ANALYSIS/11_file_io.md).
 * Generated from ida/work_file_io.i64 (tinfo_t.print); re-parses with ida_typeinf.parse_decls (checked at export).
 * Sizes: RofsDirLstHdr 24, RofsDirLstEnt 48, RofsVolume 52, RofsHandle 60, HCdvdCacheEnt 148, HCdvdRequest 868. */

struct RofsDirLstHdr
{
unsigned int count;  /* entries incl. . and .. */
unsigned int count2;  /* same value */
unsigned int dir_lba;  /* ISO LBA of this directory inside the CVM */
char marker[8];  /* #DirLst# */
unsigned int zero;  /* 0 */
};
struct RofsDirLstEnt
{
unsigned int size_lo;  /* file size low 32 bits */
unsigned int size_hi;  /* file size high 32 bits (was 'u32 0') */
unsigned int lba;  /* ISO LBA inside the CVM (0x1800 + lba*2048 in the file) */
unsigned __int8 flags;  /* bit1 = directory */
unsigned __int8 search_id;  /* ((218 + sum(toUpperFname(c))) >> 2) & 0xFF, rfdir_getSearchID 0x56BC10 */
char name[34];  /* uppercase, ';1' stripped, trailing '.' kept, NUL-terminated */
};
struct RofsVolume
{
int img_hn;  /* CVFS handle of the CVM file (CDV: device) */
int lba_offset;  /* CVM data offset in sectors (3), added in dcfReqRdCda 0x56AA98 */
int root_lba;  /* root directory LBA from PVD */
int root_size;  /* root directory size */
int dir;  /* current RofsDirLstHdr* (in-ELF table, set by ROFS_SetDir) */
unsigned __int16 pad20;
char name[8];  /* volume name VOL/BGM/BTL */
unsigned __int16 pad30;
int f32;
unsigned __int8 key[8];  /* RSU descramble key (RSU_GenerateFixedKey) */
unsigned __int8 cvm_id[8];  /* 8-byte CVM identifier */
};
struct RofsHandle
{
int size_lo;  /* file size low */
int size_hi;  /* file size high */
int rofs;  /* ROFS work area (g_rofs_work) */
int dir_idx;  /* 1-based #DirLst# index */
int start_lba;  /* file start ISO LBA */
int pos_sct;  /* current position (sectors) */
int size_sct;  /* file size in sectors */
int vol;  /* RofsVolume* */
int req_sct;  /* sectors requested */
int rd_sct;  /* sectors transferred */
int rd_rem_bytes;  /* partial sector bytes */
int sct_len;  /* sector length (2048) */
int buf;  /* destination buffer */
__int16 active;  /* 1 = handle in use */
__int16 req_state;  /* 1 = request pending, 2 = stopped */
__int16 stat;  /* 0 idle 1 complete 2 busy 3 error */
__int16 err;  /* ROFS error code */
};
struct HCdvdCacheEnt
{
int used;  /* 1 = slot in use */
int owner;  /* HCdvdRequest* + 8 (owner key) */
char name[128];  /* uppercased dir+name */
int data;  /* pointer into the loaded buffer */
int size;  /* entry size */
int zero;  /* 0 */
};
struct HCdvdRequest
{
int prev;  /* list prev */
int next;  /* list next */
int no_free;  /* nonzero = keep buffer on destroy */
int state;  /* 0 open 1 alloc/read 2 polling 3 register 4 loaded */
char path[256];  /* VOL:/... uppercased request path (backslashes) */
int buf_aligned;  /* 64-byte aligned data pointer */
int buf_raw;  /* RwHeapMalloc result */
int size_bytes2;  /* file size (copy) */
int unk284;
int unk288;
int size_bytes;  /* file size in bytes (ADXF handle +16) */
int unk296[10];
int is_archive;  /* nonzero = name-first PAK, entries indexed on load */
int adxf_hn;  /* ADXF handle while reading */
char vol_path[256];  /* VOL:NAME or BTL:NAME */
char dir_path[256];  /* VOL:/DIR/ for H_Cdvd_SetRofsDir (backslashes) */
unsigned __int16 entry_count;  /* PAK entries registered */
unsigned __int16 ref_count;  /* H_Cdvd_Request refcount */
unsigned __int16 pending_destroy;  /* destroy requested while busy */
unsigned __int16 poll_count;  /* frames spent polling */
int tail;
};
