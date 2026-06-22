// Function _DT_INIT @ 00101000

void _DT_INIT(void)

{
  if (PTR___gmon_start___00107fe8 != (undefined *)0x0) {
    (*(code *)PTR___gmon_start___00107fe8)();
  }
  return;
}



// Function FUN_00101020 @ 00101020

void FUN_00101020(void)

{
  (*(code *)PTR_00107ec0)();
  return;
}



// Function FUN_00101250 @ 00101250

void FUN_00101250(void)

{
  (*(code *)PTR___cxa_finalize_00107ff8)();
  return;
}



// Function __errno_location @ 00101260

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int * __errno_location(void)

{
  int *piVar1;

  piVar1 = (int *)(*(code *)PTR___errno_location_00107ec8)();
  return piVar1;
}



// Function strncmp @ 00101270

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int strncmp(char *__s1,char *__s2,size_t __n)

{
  int iVar1;

  iVar1 = (*(code *)PTR_strncmp_00107ed0)();
  return iVar1;
}



// Function _exit @ 00101280

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _exit(int __status)

{
  (*(code *)PTR__exit_00107ed8)();
  return;
}



// Function fread @ 00101290

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t fread(void *__ptr,size_t __size,size_t __n,FILE *__stream)

{
  size_t sVar1;

  sVar1 = (*(code *)PTR_fread_00107ee0)();
  return sVar1;
}



// Function setsockopt @ 001012a0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int setsockopt(int __fd,int __level,int __optname,void *__optval,socklen_t __optlen)

{
  int iVar1;

  iVar1 = (*(code *)PTR_setsockopt_00107ee8)();
  return iVar1;
}



// Function getpid @ 001012b0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__pid_t getpid(void)

{
  __pid_t _Var1;

  _Var1 = (*(code *)PTR_getpid_00107ef0)();
  return _Var1;
}



// Function fclose @ 001012c0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int fclose(FILE *__stream)

{
  int iVar1;

  iVar1 = (*(code *)PTR_fclose_00107ef8)();
  return iVar1;
}



// Function strlen @ 001012d0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t strlen(char *__s)

{
  size_t sVar1;

  sVar1 = (*(code *)PTR_strlen_00107f00)();
  return sVar1;
}



// Function memset @ 001012e0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memset(void *__s,int __c,size_t __n)

{
  void *pvVar1;

  pvVar1 = (void *)(*(code *)PTR_memset_00107f08)();
  return pvVar1;
}



// Function strnlen @ 001012f0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t strnlen(char *__string,size_t __maxlen)

{
  size_t sVar1;

  sVar1 = (*(code *)PTR_strnlen_00107f10)();
  return sVar1;
}



// Function close @ 00101300

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int close(int __fd)

{
  int iVar1;

  iVar1 = (*(code *)PTR_close_00107f18)();
  return iVar1;
}



// Function srand @ 00101310

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void srand(uint __seed)

{
  (*(code *)PTR_srand_00107f20)();
  return;
}



// Function fgets @ 00101320

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * fgets(char *__s,int __n,FILE *__stream)

{
  char *pcVar1;

  pcVar1 = (char *)(*(code *)PTR_fgets_00107f28)();
  return pcVar1;
}



// Function strcmp @ 00101330

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int strcmp(char *__s1,char *__s2)

{
  int iVar1;

  iVar1 = (*(code *)PTR_strcmp_00107f30)();
  return iVar1;
}



// Function signal @ 00101340

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
  __sighandler_t p_Var1;

  p_Var1 = (__sighandler_t)(*(code *)PTR_signal_00107f38)();
  return p_Var1;
}



// Function fprintf @ 00101350

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int fprintf(FILE *__stream,char *__format,...)

{
  int iVar1;

  iVar1 = (*(code *)PTR_fprintf_00107f40)();
  return iVar1;
}



// Function strtol @ 00101360

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long strtol(char *__nptr,char **__endptr,int __base)

{
  long lVar1;

  lVar1 = (*(code *)PTR_strtol_00107f48)();
  return lVar1;
}



// Function memcpy @ 00101370

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memcpy(void *__dest,void *__src,size_t __n)

{
  void *pvVar1;

  pvVar1 = (void *)(*(code *)PTR_memcpy_00107f50)();
  return pvVar1;
}



// Function time @ 00101380

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

time_t time(time_t *__timer)

{
  time_t tVar1;

  tVar1 = (*(code *)PTR_time_00107f58)();
  return tVar1;
}



// Function listen @ 00101390

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int listen(int __fd,int __n)

{
  int iVar1;

  iVar1 = (*(code *)PTR_listen_00107f60)();
  return iVar1;
}



// Function fdopen @ 001013a0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

FILE * fdopen(int __fd,char *__modes)

{
  FILE *pFVar1;

  pFVar1 = (FILE *)(*(code *)PTR_fdopen_00107f68)();
  return pFVar1;
}



// Function setvbuf @ 001013b0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int setvbuf(FILE *__stream,char *__buf,int __modes,size_t __n)

{
  int iVar1;

  iVar1 = (*(code *)PTR_setvbuf_00107f70)();
  return iVar1;
}



// Function bind @ 001013c0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int bind(int __fd,sockaddr *__addr,socklen_t __len)

{
  int iVar1;

  iVar1 = (*(code *)PTR_bind_00107f78)();
  return iVar1;
}



// Function waitpid @ 001013d0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__pid_t waitpid(__pid_t __pid,int *__stat_loc,int __options)

{
  __pid_t _Var1;

  _Var1 = (*(code *)PTR_waitpid_00107f80)();
  return _Var1;
}



// Function fopen @ 001013e0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

FILE * fopen(char *__filename,char *__modes)

{
  FILE *pFVar1;

  pFVar1 = (FILE *)(*(code *)PTR_fopen_00107f88)();
  return pFVar1;
}



// Function perror @ 001013f0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void perror(char *__s)

{
  (*(code *)PTR_perror_00107f90)();
  return;
}



// Function strtok @ 00101400

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strtok(char *__s,char *__delim)

{
  char *pcVar1;

  pcVar1 = (char *)(*(code *)PTR_strtok_00107f98)();
  return pcVar1;
}



// Function accept @ 00101410

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int accept(int __fd,sockaddr *__addr,socklen_t *__addr_len)

{
  int iVar1;

  iVar1 = (*(code *)PTR_accept_00107fa0)();
  return iVar1;
}



// Function exit @ 00101420

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void exit(int __status)

{
  (*(code *)PTR_exit_00107fa8)();
  return;
}



// Function fwrite @ 00101430

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

{
  size_t sVar1;

  sVar1 = (*(code *)PTR_fwrite_00107fb0)();
  return sVar1;
}



// Function getrandom @ 00101440

void getrandom(void)

{
  (*(code *)PTR_getrandom_00107fb8)();
  return;
}



// Function fork @ 00101450

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__pid_t fork(void)

{
  __pid_t _Var1;

  _Var1 = (*(code *)PTR_fork_00107fc0)();
  return _Var1;
}



// Function rand @ 00101460

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int rand(void)

{
  int iVar1;

  iVar1 = (*(code *)PTR_rand_00107fc8)();
  return iVar1;
}



// Function socket @ 00101470

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int socket(int __domain,int __type,int __protocol)

{
  int iVar1;

  iVar1 = (*(code *)PTR_socket_00107fd0)();
  return iVar1;
}



// Function FUN_00101480 @ 00101480

void FUN_00101480(void)

{
  perror("flag");
                    /* WARNING: Subroutine does not return */
  exit(1);
}



// Function FUN_00101510 @ 00101510

undefined8 FUN_00101510(void)

{
  undefined8 uVar1;
  int __fd;
  int iVar2;
  __pid_t _Var3;
  FILE *__stream;
  size_t sVar4;
  int *piVar5;
  size_t sVar6;
  undefined1 auVar7 [16];
  undefined8 uStack_38;
  undefined1 auStack_30 [4];
  undefined4 local_2c;
  sockaddr local_28;

  local_2c = 1;
  __stream = fopen("/app/flag.txt","r");
  if (__stream == (FILE *)0x0) {
    perror("flag");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  sVar4 = fread(&DAT_00108040,1,0x7f,__stream);
  fclose(__stream);
  do {
    sVar6 = sVar4;
    if (sVar6 == 0) {
      DAT_00108040 = 0;
      fwrite("empty flag\n",1,0xb,stderr);
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    sVar4 = sVar6 - 1;
  } while (((&DAT_0010803f)[sVar6] == '\n') || ((&DAT_0010803f)[sVar6] == '\r'));
  (&DAT_00108040)[sVar6] = 0;
  signal(0x11,FUN_00101820);
  signal(0xd,(__sighandler_t)0x1);
  __fd = socket(2,1,0);
  if (__fd < 0) {
    perror("socket");
  }
  else {
    iVar2 = setsockopt(__fd,1,2,&local_2c,4);
    if (iVar2 < 0) {
      perror("setsockopt");
      close(__fd);
    }
    else {
      local_28.sa_data[2] = '\0';
      local_28.sa_data[3] = '\0';
      local_28.sa_data[4] = '\0';
      local_28.sa_data[5] = '\0';
      local_28.sa_data[6] = '\0';
      local_28.sa_data[7] = '\0';
      local_28.sa_data[8] = '\0';
      local_28.sa_data[9] = '\0';
      local_28.sa_data[10] = '\0';
      local_28.sa_data[0xb] = '\0';
      local_28.sa_data[0xc] = '\0';
      local_28.sa_data[0xd] = '\0';
      local_28.sa_family = 2;
      local_28.sa_data[0] = 'N';
      local_28.sa_data[1] = ' ';
      iVar2 = bind(__fd,&local_28,0x10);
      if (iVar2 < 0) {
        perror("bind");
        close(__fd);
      }
      else {
        iVar2 = listen(__fd,0x10);
        if (-1 < iVar2) {
          do {
            while (iVar2 = accept(__fd,(sockaddr *)0x0,(socklen_t *)0x0), -1 < iVar2) {
              _Var3 = fork();
              if (_Var3 == 0) {
                close(__fd);
                auVar7 = FUN_001025f0(iVar2);
                uVar1 = uStack_38;
                uStack_38 = auVar7._0_8_;
                (*(code *)PTR___libc_start_main_00107fd8)
                          (FUN_00101510,uVar1,auStack_30,0,0,auVar7._8_8_,&uStack_38);
                do {
                    /* WARNING: Do nothing block with infinite loop */
                } while( true );
              }
              close(iVar2);
            }
            piVar5 = __errno_location();
          } while (*piVar5 == 4);
          perror("accept");
          close(__fd);
          return 0;
        }
        perror("listen");
        close(__fd);
      }
    }
  }
  return 1;
}



// Function entry @ 001016c0

void processEntry entry(undefined8 param_1,undefined8 param_2)

{
  undefined1 auStack_8 [8];

  (*(code *)PTR___libc_start_main_00107fd8)
            (FUN_00101510,param_2,&stack0x00000008,0,0,param_1,auStack_8);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// Function FUN_001016f0 @ 001016f0

/* WARNING: Removing unreachable block (ram,0x00101703) */
/* WARNING: Removing unreachable block (ram,0x0010170f) */

void FUN_001016f0(void)

{
  return;
}



// Function FUN_00101720 @ 00101720

/* WARNING: Removing unreachable block (ram,0x00101744) */
/* WARNING: Removing unreachable block (ram,0x00101750) */

void FUN_00101720(void)

{
  return;
}



// Function _FINI_0 @ 00101760

void _FINI_0(void)

{
  if (DAT_00108028 == '\0') {
    if (PTR___cxa_finalize_00107ff8 != (undefined *)0x0) {
      FUN_00101250(PTR_LOOP_00108008);
    }
    FUN_001016f0();
    DAT_00108028 = 1;
    return;
  }
  return;
}



// Function _INIT_0 @ 001017a0

void _INIT_0(void)

{
  FUN_00101720();
  return;
}



// Function FUN_001017b0 @ 001017b0

void FUN_001017b0(long param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  ulong uVar4;
  undefined8 *puVar5;

  *(undefined8 *)(param_1 + 0x758) = 0;
  *(undefined8 *)(param_1 + 0x7c4) = 0;
  puVar5 = (undefined8 *)(param_1 + 0x760U & 0xfffffffffffffff8);
  uVar4 = (ulong)(((int)param_1 - (int)puVar5) + 0x7ccU >> 3);
  for (; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  bVar1 = *(byte *)(param_1 + 0xc);
  if (bVar1 != 0) {
    bVar2 = *(byte *)(param_1 + 10);
    uVar4 = 0;
    do {
      bVar3 = *(byte *)(param_1 + 0x53e + uVar4 * 4);
      if (bVar3 < bVar2) {
        *(undefined4 *)(param_1 + 0x7b8 + uVar4 * 4) =
             *(undefined4 *)(param_1 + 0x51e + (ulong)bVar3 * 4);
      }
      uVar4 = uVar4 + 1;
    } while ((uVar4 != 4) && (uVar4 < bVar1));
  }
  return;
}



// Function FUN_00101820 @ 00101820

void FUN_00101820(void)

{
  __pid_t _Var1;

  do {
    _Var1 = waitpid(-1,(int *)0x0,1);
  } while (0 < _Var1);
  return;
}



// Function FUN_00101850 @ 00101850

void FUN_00101850(FILE *param_1)

{
  fwrite("commands:\n",1,10,param_1);
  fwrite("  help\n",1,7,param_1);
  fwrite("  status\n",1,9,param_1);
  fwrite("  upload <slot> <hex_wasm>\n",1,0x1b,param_1);
  fwrite("  inspect <slot>\n",1,0x11,param_1);
  fwrite("  warm <slot> <hex_profile>\n",1,0x1c,param_1);
  fwrite("  sync <slot>\n",1,0xe,param_1);
  fwrite("  quote <slot> <hex_receipt>\n",1,0x1d,param_1);
  fwrite("  attest <slot> <hex_witness>\n",1,0x1e,param_1);
  fwrite("  bless <slot>\n",1,0xf,param_1);
  fwrite("  activate <slot> <sealhex>\n",1,0x1c,param_1);
  fwrite("  invoke <export_name>\n",1,0x17,param_1);
  fwrite("  flag\n",1,7,param_1);
  fwrite("  quit\n",1,7,param_1);
  return;
}



// Function FUN_001019c0 @ 001019c0

uint FUN_001019c0(void)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  time_t tVar4;
  uint local_1c [3];

  local_1c[0] = 0;
  lVar3 = getrandom(local_1c,4,0);
  if (lVar3 != 4) {
    tVar4 = time((time_t *)0x0);
    uVar1 = getpid();
    srand(uVar1 ^ (uint)tVar4 ^ (uint)local_1c);
    iVar2 = rand();
    local_1c[0] = rand();
    local_1c[0] = iVar2 << 0x10 ^ local_1c[0];
  }
  return local_1c[0];
}



// Function FUN_00101a30 @ 00101a30

undefined8 FUN_00101a30(char *param_1,undefined1 *param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  char *local_20 [2];

  local_20[0] = (char *)0x0;
  uVar1 = strtol(param_1,local_20,10);
  uVar2 = 0;
  if (((*param_1 != '\0') && (*local_20[0] == '\0')) && (uVar1 < 0x100)) {
    *param_2 = (char)uVar1;
    uVar2 = 1;
  }
  return uVar2;
}



// Function FUN_00101a80 @ 00101a80

ulong FUN_00101a80(FILE *param_1,long param_2,long param_3,char *param_4,byte param_5,uint param_6)

{
  char cVar1;
  ulong uVar2;
  ulong uVar3;

  cVar1 = *param_4;
  if (cVar1 == '\0') {
    uVar2 = *(ulong *)(param_2 + 8000);
    uVar3 = uVar2 & 0xffffffff;
    if (0xff < uVar2) {
      uVar3 = uVar2 & 0xff;
    }
    return uVar3;
  }
  if (cVar1 != '\x01') {
    if ((((cVar1 == '\x02') && (-1 < *(int *)(param_2 + 0x1f38))) &&
        (param_3 == (long)*(int *)(param_2 + 0x1f38) * 0x7cc + param_2)) &&
       (((param_4[1] == '\x01' && (param_4[2] == '\x01')) && ((param_4[3] & 1U) != 0)))) {
      *(undefined8 *)(param_2 + 8000) = 0;
      *(undefined4 *)(param_2 + 0x1f3c) = 1;
      return 1;
    }
    return 0xffffffff;
  }
  fprintf(param_1,"lane[%u] log:%d\n",(ulong)param_5,(ulong)param_6);
  return 0x7f;
}



// Function FUN_00101b40 @ 00101b40

uint FUN_00101b40(long param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  size_t sVar7;
  long lVar8;
  byte *pbVar9;
  uint uVar10;
  ulong uVar11;
  long lVar12;
  ulong uVar13;
  byte *pbVar14;

  bVar1 = *(byte *)(param_1 + 7);
  bVar2 = *(byte *)(param_1 + 6);
  bVar3 = *(byte *)(param_1 + 10);
  bVar4 = *(byte *)(param_1 + 0xb);
  bVar5 = *(byte *)(param_1 + 0xc);
  uVar10 = (((((((*(byte *)(param_1 + 3) ^ 0xd74ea890) * 0x1000193 ^ (uint)*(byte *)(param_1 + 5) ^
                0x811c9dc5) * 0x1000193 ^ (uint)bVar2 ^ 0x811c9dc5) * 0x1000193 ^ (uint)bVar1 ^
              0x811c9dc5) * 0x1000193 ^ (uint)bVar3 ^ 0x811c9dc5) * 0x1000193 ^ (uint)bVar4 ^
            0x811c9dc5) * 0x1000193 ^ (uint)bVar5 ^ 0x811c9dc5) * 0x1000193;
  if (bVar1 != 0) {
    pbVar14 = (byte *)(param_1 + 0xe);
    uVar13 = 0;
    do {
      uVar10 = uVar10 ^ 0x811c9dc5;
      sVar7 = strnlen((char *)pbVar14,0x10);
      if (sVar7 != 0) {
        pbVar9 = pbVar14;
        do {
          bVar6 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          uVar10 = (uVar10 ^ bVar6) * 0x1000193;
        } while (pbVar14 + sVar7 != pbVar9);
      }
      pbVar9 = pbVar14 + 0x10;
      uVar13 = uVar13 + 1;
      pbVar14 = pbVar14 + 0x14;
      uVar10 = (*pbVar9 ^ uVar10 ^ 0x811c9dc5) * 0x1000193;
    } while ((uVar13 < bVar1) && (uVar13 != 6));
  }
  if (bVar2 != 0) {
    pbVar14 = (byte *)(param_1 + 0x9e);
    uVar13 = 0;
    do {
      uVar11 = (ulong)*(ushort *)(param_1 + 0x86 + uVar13 * 2);
      uVar10 = ((uint)*(byte *)(param_1 + 0x87 + uVar13 * 2) ^
               (*(byte *)(param_1 + 0x86 + uVar13 * 2) ^ uVar10 ^ 0x811c9dc5) * 0x1000193) *
               0x1000193 ^ 0x811c9dc5;
      if (uVar11 != 0) {
        pbVar9 = pbVar14;
        do {
          bVar1 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          uVar10 = (bVar1 ^ uVar10) * 0x1000193;
        } while (pbVar14 + uVar11 != pbVar9);
      }
      uVar13 = uVar13 + 1;
      pbVar14 = pbVar14 + 0x60;
    } while ((uVar13 != 6) && (uVar13 < (uint)bVar2));
  }
  if (bVar3 != 0) {
    lVar12 = param_1 + 0x51e;
    uVar13 = 0;
    do {
      uVar10 = uVar10 ^ 0x811c9dc5;
      lVar8 = 0;
      do {
        pbVar14 = (byte *)(lVar12 + lVar8);
        lVar8 = lVar8 + 1;
        uVar10 = (*pbVar14 ^ uVar10) * 0x1000193;
      } while (lVar8 != 4);
      uVar13 = uVar13 + 1;
      lVar12 = lVar12 + 4;
    } while ((uVar13 < bVar3) && (uVar13 != 4));
  }
  if (bVar4 != 0) {
    lVar12 = param_1 + 0x52e;
    uVar13 = 0;
    do {
      uVar10 = uVar10 ^ 0x811c9dc5;
      lVar8 = 0;
      do {
        pbVar14 = (byte *)(lVar12 + lVar8);
        lVar8 = lVar8 + 1;
        uVar10 = (*pbVar14 ^ uVar10) * 0x1000193;
      } while (lVar8 != 4);
      uVar13 = uVar13 + 1;
      lVar12 = lVar12 + 4;
    } while ((uVar13 != 4) && (uVar13 < bVar4));
  }
  if (bVar5 != 0) {
    param_1 = param_1 + 0x53e;
    uVar13 = 0;
    do {
      uVar10 = uVar10 ^ 0x811c9dc5;
      lVar12 = 0;
      do {
        pbVar14 = (byte *)(param_1 + lVar12);
        lVar12 = lVar12 + 1;
        uVar10 = (*pbVar14 ^ uVar10) * 0x1000193;
      } while (lVar12 != 4);
      uVar13 = uVar13 + 1;
      param_1 = param_1 + 4;
    } while ((uVar13 < bVar5) && (uVar13 != 4));
  }
  return uVar10;
}



// Function FUN_00101dd0 @ 00101dd0

undefined8 FUN_00101dd0(char *param_1,long param_2,ulong *param_3,ulong param_4)

{
  int iVar1;
  size_t sVar2;
  ulong uVar3;
  ulong uVar4;
  byte bVar5;
  char cVar6;

  sVar2 = strlen(param_1);
  if (((sVar2 & 1) != 0) || (param_4 < sVar2 >> 1)) {
    return 0;
  }
  uVar4 = (ulong)((uint)sVar2 & 1);
  if (sVar2 != 0) {
    do {
      cVar6 = param_1[uVar4];
      iVar1 = (int)cVar6;
      if ((byte)(cVar6 - 0x30U) < 10) {
        cVar6 = param_1[uVar4 + 1];
        iVar1 = iVar1 + -0x30;
        if ((byte)(cVar6 - 0x30U) < 10) goto LAB_00101e95;
LAB_00101e3e:
        if (5 < (byte)(cVar6 + 0x9fU)) goto LAB_00101e4c;
LAB_00101ee0:
        bVar5 = cVar6 + 0xa9;
      }
      else {
        if ((byte)(cVar6 + 0x9fU) < 6) {
          cVar6 = param_1[uVar4 + 1];
          iVar1 = iVar1 + -0x57;
          if ((byte)(cVar6 - 0x30U) < 10) goto LAB_00101e95;
          if ((byte)(cVar6 + 0x9fU) < 6) goto LAB_00101ee0;
        }
        else {
          if ((byte)(cVar6 + 0xbfU) < 6) {
            cVar6 = param_1[uVar4 + 1];
            iVar1 = iVar1 + -0x37;
            if (9 < (byte)(cVar6 - 0x30U)) goto LAB_00101e3e;
LAB_00101e95:
            bVar5 = cVar6 - 0x30;
            goto LAB_00101e5e;
          }
          cVar6 = param_1[uVar4 + 1];
          if ((byte)(cVar6 - 0x30U) < 10) {
            return 0;
          }
          if ((byte)(cVar6 + 0x9fU) < 6) {
            return 0;
          }
          iVar1 = -1;
        }
LAB_00101e4c:
        if (5 < (byte)(cVar6 + 0xbfU)) {
          return 0;
        }
        bVar5 = cVar6 - 0x37;
        if (iVar1 == -1) {
          return 0;
        }
      }
LAB_00101e5e:
      uVar3 = uVar4 + 2;
      *(byte *)(param_2 + (uVar4 >> 1)) = (byte)(iVar1 << 4) | bVar5;
      uVar4 = uVar3;
    } while (uVar3 < sVar2);
  }
  *param_3 = sVar2 >> 1;
  return 1;
}



// Function FUN_00101f20 @ 00101f20

void FUN_00101f20(FILE *param_1,long param_2,byte param_3,undefined8 param_4)

{
  long lVar1;
  undefined1 (*pauVar2) [16];
  long lVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  ulong uVar7;
  ulong uVar8;
  byte *pbVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  char cVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  undefined8 *puVar17;
  char *pcVar18;
  long lVar19;
  uint uVar20;
  long lVar21;
  byte bVar22;
  ulong local_240;
  byte local_238 [520];

  bVar22 = 0;
  local_240 = 0;
  if (3 < param_3) {
    fwrite("ERR bad slot\n",1,0xd,param_1);
    return;
  }
  lVar21 = (ulong)param_3 * 0x7cc;
  pcVar18 = (char *)(param_2 + lVar21);
  if ((*pcVar18 == '\0') || (pcVar18[1] == '\0')) {
    fwrite("ERR slot not warmable\n",1,0x16,param_1);
    return;
  }
  iVar5 = FUN_00101dd0(param_4,local_238,&local_240,0x200);
  uVar8 = local_240;
  if (iVar5 == 0) {
    fwrite("ERR bad profile\n",1,0x10,param_1);
    return;
  }
  uVar16 = (uint)param_3;
  puVar17 = (undefined8 *)(param_2 + 0x6e4 + lVar21);
  pauVar2 = (undefined1 (*) [16])(param_2 + 0x69c + lVar21);
  bVar4 = param_3 + 3 & 0x1f;
  uVar6 = (uint)(byte)pcVar18[0xc] * 0x45d9f3b ^ *(uint *)(param_2 + 0x1f48) ^
          (*(uint *)(pcVar18 + 0x694) << bVar4 | *(uint *)(pcVar18 + 0x694) >> 0x20 - bVar4) ^
          (uint)(byte)pcVar18[9] * -0x61c88647 ^ 0x5741524d;
  if (local_240 == 0) {
    *(undefined8 *)pauVar2[4] = 0;
    *pauVar2 = (undefined1  [16])0x0;
    pauVar2[1] = (undefined1  [16])0x0;
    pauVar2[2] = (undefined1  [16])0x0;
    pauVar2[3] = (undefined1  [16])0x0;
    *puVar17 = 0;
    *(undefined8 *)((long)puVar17 + 0x6c) = 0;
    uVar8 = (ulong)(((int)puVar17 - (int)(undefined8 *)((ulong)(puVar17 + 1) & 0xfffffffffffffff8))
                    + 0x74U >> 3);
    puVar17 = (undefined8 *)((ulong)(puVar17 + 1) & 0xfffffffffffffff8);
    for (; uVar8 != 0; uVar8 = uVar8 - 1) {
      *puVar17 = 0;
      puVar17 = puVar17 + (ulong)bVar22 * -2 + 1;
    }
    FUN_001017b0(pcVar18);
  }
  else {
    pbVar9 = local_238;
    do {
      uVar6 = uVar6 * 0x19660d + 0x3c6ef35f;
      *pbVar9 = *pbVar9 ^ (byte)(uVar6 >> 0x18);
      pbVar9 = pbVar9 + 1;
    } while (pbVar9 != local_238 + local_240);
    *pauVar2 = (undefined1  [16])0x0;
    *(undefined8 *)pauVar2[4] = 0;
    pauVar2[1] = (undefined1  [16])0x0;
    pauVar2[2] = (undefined1  [16])0x0;
    pauVar2[3] = (undefined1  [16])0x0;
    *puVar17 = 0;
    *(undefined8 *)((long)puVar17 + 0x6c) = 0;
    uVar7 = (ulong)(((int)puVar17 - (int)(undefined8 *)((ulong)(puVar17 + 1) & 0xfffffffffffffff8))
                    + 0x74U >> 3);
    puVar17 = (undefined8 *)((ulong)(puVar17 + 1) & 0xfffffffffffffff8);
    for (; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar17 = 0;
      puVar17 = puVar17 + (ulong)bVar22 * -2 + 1;
    }
    FUN_001017b0(pcVar18);
    uVar6 = 0;
    iVar5 = 0;
    uVar7 = 0;
    while( true ) {
      uVar10 = uVar7 + 1;
      uVar6 = uVar6 | (local_238[uVar7] & 0x7f) << ((byte)iVar5 & 0x1f);
      if (-1 < (char)local_238[uVar7]) break;
      iVar5 = iVar5 + 7;
      if ((uVar8 <= uVar10) || (uVar7 = uVar10, iVar5 == 0x23)) goto LAB_001020c7;
    }
    if (uVar6 - 1 < 0x10) {
      lVar3 = param_2 + 0x6a0 + lVar21;
      uVar20 = 0;
      lVar1 = param_2 + (long)(int)uVar16 * 0x7cc;
      goto LAB_00102160;
    }
  }
LAB_001020c7:
  fwrite("ERR profile header\n",1,0x13,param_1);
  return;
LAB_00102160:
  if (uVar8 <= uVar10) {
LAB_0010218f:
    fwrite("ERR profile decode\n",1,0x13,param_1);
    return;
  }
  uVar12 = 0;
  iVar5 = 0;
  uVar7 = uVar10;
  while( true ) {
    uVar11 = uVar7 + 1;
    bVar22 = (byte)iVar5 & 0x1f;
    uVar14 = (uint)uVar12 | (local_238[uVar7] & 0x7f) << bVar22;
    uVar12 = (ulong)uVar14;
    if (-1 < (char)local_238[uVar7]) break;
    iVar5 = iVar5 + 7;
    if ((uVar8 <= uVar11) || (uVar7 = uVar11, iVar5 == 0x23)) goto LAB_0010218f;
  }
  if (uVar14 == 0) {
    if (uVar8 <= uVar11) {
LAB_001022f2:
      fwrite("ERR add decode\n",1,0xf,param_1);
      return;
    }
    iVar5 = 0;
    while( true ) {
      uVar7 = uVar11 + 1;
      uVar14 = (uint)uVar12 | (local_238[uVar11] & 0x7f) << ((byte)iVar5 & 0x1f);
      uVar12 = (ulong)uVar14;
      if (-1 < (char)local_238[uVar11]) break;
      iVar5 = iVar5 + 7;
      if ((uVar8 <= uVar7) || (uVar11 = uVar7, iVar5 == 0x23)) goto LAB_001022f2;
    }
    uVar10 = uVar12 + uVar7;
    if (uVar8 < uVar10) goto LAB_001022f2;
    if (0x40 - *(byte *)(lVar1 + 0x69c) < uVar14) goto LAB_00102380;
    memcpy((void *)(lVar3 + (ulong)*(byte *)(lVar1 + 0x69c)),local_238 + uVar7,uVar12);
    cVar13 = (char)uVar14 + *(char *)(lVar1 + 0x69c);
  }
  else if (uVar14 == 1) {
    if (uVar8 <= uVar11) {
LAB_00102490:
      fwrite("ERR copy decode\n",1,0x10,param_1);
      return;
    }
    uVar7 = (ulong)(uint)(0 << bVar22);
    iVar5 = 0;
    while( true ) {
      uVar12 = uVar11 + 1;
      uVar14 = (uint)uVar7 | (local_238[uVar11] & 0x7f) << ((byte)iVar5 & 0x1f);
      uVar7 = (ulong)uVar14;
      if (-1 < (char)local_238[uVar11]) break;
      iVar5 = iVar5 + 7;
      if ((iVar5 == 0x23) || (uVar11 = uVar12, uVar8 <= uVar12)) goto LAB_00102490;
    }
    if (uVar8 <= uVar12) goto LAB_00102490;
    uVar15 = 0;
    iVar5 = 0;
    while( true ) {
      uVar10 = uVar12 + 1;
      uVar15 = uVar15 | (local_238[uVar12] & 0x7f) << ((byte)iVar5 & 0x1f);
      if (-1 < (char)local_238[uVar12]) break;
      iVar5 = iVar5 + 7;
      if ((uVar8 <= uVar10) || (uVar12 = uVar10, iVar5 == 0x23)) goto LAB_00102490;
    }
    if ((uint)(byte)pcVar18[8] < uVar14 + uVar15) goto LAB_00102490;
    lVar19 = (long)(int)uVar16 * 0x7cc + param_2;
    bVar22 = *(byte *)(lVar19 + 0x69c);
    if (0x40 - bVar22 < uVar15) goto LAB_00102380;
    memcpy((void *)(lVar3 + (ulong)bVar22),(void *)(lVar21 + 0x54e + uVar7 + param_2),(ulong)uVar15)
    ;
    cVar13 = (char)uVar15 + *(char *)(lVar19 + 0x69c);
  }
  else if (uVar14 == 2) {
    if ((uVar8 <= uVar11) || (uVar8 <= uVar7 + 2)) {
LAB_001023d5:
      fwrite("ERR run decode\n",1,0xf,param_1);
      return;
    }
    uVar14 = 0;
    iVar5 = 0;
    uVar12 = uVar7 + 2;
    while( true ) {
      uVar10 = uVar12 + 1;
      uVar14 = uVar14 | (local_238[uVar12] & 0x7f) << ((byte)iVar5 & 0x1f);
      if (-1 < (char)local_238[uVar12]) break;
      iVar5 = iVar5 + 7;
      if ((iVar5 == 0x23) || (uVar12 = uVar10, uVar8 <= uVar10)) goto LAB_001023d5;
    }
    if (0x40 - *(byte *)(lVar1 + 0x69c) < uVar14) {
LAB_00102380:
      fwrite("ERR cache reject\n",1,0x11,param_1);
      return;
    }
    memset((void *)((ulong)*(byte *)(lVar1 + 0x69c) + lVar3),(uint)local_238[uVar7 + 1],
           (ulong)uVar14);
    cVar13 = (char)uVar14 + *(char *)(lVar1 + 0x69c);
  }
  else {
    if (uVar14 != 3) {
      fwrite("ERR bad opcode\n",1,0xf,param_1);
      return;
    }
    if (uVar8 <= uVar11) {
LAB_001021ff:
      fwrite("ERR seek decode\n",1,0x10,param_1);
      return;
    }
    uVar14 = 0;
    iVar5 = 0;
    while( true ) {
      uVar10 = uVar11 + 1;
      uVar14 = uVar14 | (local_238[uVar11] & 0x7f) << ((byte)iVar5 & 0x1f);
      if (-1 < (char)local_238[uVar11]) break;
      iVar5 = iVar5 + 7;
      if ((iVar5 == 0x23) || (uVar11 = uVar10, uVar8 <= uVar10)) goto LAB_001021ff;
    }
    if (0x40 - *(byte *)(lVar1 + 0x69c) < uVar14) goto LAB_001021ff;
    memset((void *)(lVar3 + (ulong)*(byte *)(lVar1 + 0x69c)),0,(ulong)uVar14);
    cVar13 = (char)uVar14 + *(char *)(lVar1 + 0x69c);
  }
  uVar20 = uVar20 + 1;
  lVar19 = param_2 + (long)(int)uVar16 * 0x7cc;
  *(char *)(lVar19 + 0x69c) = cVar13;
  if (uVar20 == uVar6) {
    *(undefined2 *)(param_2 + 0x69d + (long)(int)uVar16 * 0x7cc) = 1;
    *(undefined4 *)(lVar19 + 0x6e0) = 0;
    fprintf(param_1,"OK warmed slot %u image_len=%u\n",(ulong)uVar16,
            (ulong)*(byte *)(lVar19 + 0x69c));
    return;
  }
  goto LAB_00102160;
}



// Function FUN_001025f0 @ 001025f0

void FUN_001025f0(int param_1)

{
  byte *pbVar1;
  undefined8 uVar2;
  undefined1 auVar3 [16];
  byte bVar4;
  byte bVar5;
  char cVar6;
  undefined4 uVar7;
  ushort uVar8;
  short sVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  bool bVar14;
  undefined4 uVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  FILE *__stream;
  char *pcVar19;
  size_t sVar20;
  char *__s2;
  char *pcVar21;
  undefined8 *puVar22;
  undefined4 *puVar23;
  byte bVar24;
  byte bVar25;
  long lVar26;
  ulong uVar27;
  ulong uVar28;
  uint uVar29;
  byte *pbVar30;
  ulong uVar31;
  undefined4 *puVar32;
  long lVar33;
  undefined1 *puVar34;
  undefined1 uVar35;
  byte bVar36;
  uint uVar37;
  undefined1 *puVar38;
  undefined4 *puVar39;
  undefined8 *puVar40;
  undefined1 *puVar41;
  undefined4 *puVar42;
  long lVar43;
  undefined1 *puVar44;
  long lVar45;
  ulong uVar46;
  ulong uVar47;
  long lVar48;
  ulong uVar49;
  byte bVar50;
  undefined1 local_5030 [120];
  byte abStack_4fb8 [48];
  byte abStack_4f88 [4096];
  byte abStack_3f88 [1680];
  int aiStack_38f8 [3];
  byte abStack_38ec [68];
  uint uStack_38a8;
  byte abStack_38a4 [112];
  uint uStack_3834;
  byte abStack_3830 [112];
  uint auStack_37c0 [3556];

  bVar50 = 0;
  puVar44 = &stack0xffffffffffffffd0;
  do {
    puVar34 = puVar44;
    *(undefined8 *)(puVar34 + -0x1000) = *(undefined8 *)(puVar34 + -0x1000);
    puVar44 = puVar34 + -0x1000;
  } while (puVar34 + -0x1000 != local_5030);
  *(undefined1 **)(puVar34 + -0x1010) = puVar34 + 0xa8;
  puVar40 = (undefined8 *)(puVar34 + 0xa8);
  for (lVar26 = 0x3ea; lVar26 != 0; lVar26 = lVar26 + -1) {
    *puVar40 = 0;
    puVar40 = puVar40 + 1;
  }
  *(undefined8 *)(puVar34 + -0x1020) = 0x102635;
  uVar15 = FUN_001019c0();
  *(undefined4 *)(puVar34 + 0x1fd8) = uVar15;
  *(undefined8 *)(puVar34 + -0x1020) = 0x102641;
  uVar15 = FUN_001019c0();
  puVar34[0x1fdc] = 1;
  *(undefined4 *)(puVar34 + 0x1ff0) = uVar15;
  *(undefined4 *)(puVar34 + 0x1fe0) = 0xffffffff;
  *(undefined8 *)(puVar34 + 0x1fe8) = 0x7a69;
  *(undefined8 *)(puVar34 + -0x1020) = 0x102675;
  __stream = fdopen(param_1,"r+");
  if (__stream == (FILE *)0x0) {
    *(undefined8 *)(puVar34 + -0x1020) = 0x104d2e;
    close(param_1);
                    /* WARNING: Subroutine does not return */
    *(undefined8 *)(puVar34 + -0x1020) = 0x104d38;
    _exit(1);
  }
  *(undefined8 *)(puVar34 + -0x1020) = 0x102699;
  setvbuf(__stream,(char *)0x0,2,0);
  *(undefined8 *)(puVar34 + -0x1020) = 0x1026b2;
  fwrite("Canopy Cache uplink v5\n",1,0x17,__stream);
  *(undefined8 *)(puVar34 + -0x1020) = 0x1026ba;
  FUN_00101850(__stream);
  *(undefined8 *)(puVar34 + -0x1020) = 0x1026d3;
  fwrite(&DAT_001061dc,1,2,__stream);
  *(undefined1 **)(puVar34 + -0x1018) = puVar34 + 0x1ff8;
LAB_001026e0:
  *(undefined8 *)(puVar34 + -0x1020) = 0x1026f1;
  pcVar19 = fgets(*(char **)(puVar34 + -0x1018),0x2000,__stream);
  if (pcVar19 == (char *)0x0) {
LAB_00102922:
    *(undefined8 *)(puVar34 + -0x1020) = 0x10292a;
    fclose(__stream);
                    /* WARNING: Subroutine does not return */
    *(undefined8 *)(puVar34 + -0x1020) = 0x102931;
    _exit(0);
  }
  *(undefined8 *)(puVar34 + -0x1020) = 0x102703;
  sVar20 = strlen(*(char **)(puVar34 + -0x1018));
  lVar26 = *(long *)(puVar34 + -0x1018);
  while (sVar20 != 0) {
    sVar20 = sVar20 - 1;
    cVar6 = *(char *)(lVar26 + sVar20);
    if ((cVar6 != '\n') && (cVar6 != '\r')) break;
    *(undefined1 *)(lVar26 + sVar20) = 0;
  }
  *(undefined8 *)(puVar34 + -0x1020) = 0x102737;
  pcVar19 = strtok(*(char **)(puVar34 + -0x1018)," ");
  *(undefined8 *)(puVar34 + -0x1020) = 0x102744;
  __s2 = strtok((char *)0x0," ");
  *(undefined8 *)(puVar34 + -0x1020) = 0x102751;
  pcVar21 = strtok((char *)0x0," ");
  if ((pcVar19 == (char *)0x0) || (*pcVar19 == '\0')) goto LAB_001027e0;
  *(undefined8 *)(puVar34 + -0x1020) = 0x102772;
  iVar16 = strcmp(pcVar19,"help");
  if (iVar16 == 0) {
    *(undefined8 *)(puVar34 + -0x1020) = 0x102808;
    FUN_00101850(__stream);
    goto LAB_001027e0;
  }
  *(undefined8 *)(puVar34 + -0x1020) = 0x102789;
  iVar16 = strcmp(pcVar19,"status");
  if (iVar16 == 0) {
    *(undefined8 *)(puVar34 + -0x1020) = 0x102885;
    fprintf(__stream,"session_hint=0x%08x\n",
            (ulong)(((*(uint *)(puVar34 + 0x1ff0) ^ 0xa5c31f27) << 7 |
                    (*(uint *)(puVar34 + 0x1ff0) ^ 0xa5c31f27) >> 0x19) + 0x19d3b42e));
    *(undefined8 *)(puVar34 + -0x1020) = 0x10289e;
    fprintf(__stream,"vault_balance=%llu\n",*(undefined8 *)(puVar34 + 0x1fe8));
    *(undefined8 *)(puVar34 + -0x1020) = 0x1028b6;
    fprintf(__stream,"active_slot=%d\n",(ulong)*(uint *)(puVar34 + 0x1fe0));
    goto LAB_001027e0;
  }
  *(undefined8 *)(puVar34 + -0x1020) = 0x1027a0;
  iVar16 = strcmp(pcVar19,"upload");
  if (iVar16 == 0) {
    if ((__s2 == (char *)0x0) || (pcVar21 == (char *)0x0)) {
LAB_001027c5:
      *(undefined8 *)(puVar34 + -0x1020) = 0x1027de;
      fwrite("ERR usage upload <slot> <hex_wasm>\n",1,0x23,__stream);
      goto LAB_001027e0;
    }
    *(undefined4 *)(puVar34 + -0x1008) = 0;
    *(undefined8 *)(puVar34 + -0x1020) = 0x1027bc;
    pcVar19 = strtok((char *)0x0," ");
    if (pcVar19 != (char *)0x0) goto LAB_001027c5;
    *(undefined8 *)(puVar34 + -0x1020) = 0x1029dc;
    iVar16 = FUN_00101a30(__s2,puVar34 + -0xf91);
    if (iVar16 == 0) {
LAB_00102c06:
      *(undefined8 *)(puVar34 + -0x1020) = 0x102c1f;
      fwrite("ERR bad slot\n",1,0xd,__stream);
      goto LAB_001027e0;
    }
    bVar25 = puVar34[-0xf91];
    *(undefined8 *)(puVar34 + -0xf88) = 0;
    if (3 < bVar25) goto LAB_00102c06;
    *(undefined4 *)(puVar34 + -0x1008) = *(undefined4 *)(puVar34 + -0x1008);
    *(undefined8 *)(puVar34 + -0x1020) = 0x102a2a;
    iVar17 = FUN_00101dd0(pcVar21,puVar34 + -0xf58,puVar34 + -0xf88,0x1000);
    iVar16 = *(int *)(puVar34 + -0x1008);
    if (iVar17 == 0) {
      *(undefined8 *)(puVar34 + -0x1020) = 0x1035a7;
      fwrite("ERR bad hex\n",1,0xc,__stream);
      goto LAB_001027e0;
    }
    uVar27 = *(ulong *)(puVar34 + -0xf88);
    if (((((((7 < uVar27) && (*(long *)(puVar34 + -0xf58) == 0x16d736100)) && (10 < uVar27)) &&
          ((bVar36 = puVar34[-0xf4f], puVar34[-0xf50] == '\0' && (4 < bVar36)))) &&
         ((ulong)bVar36 + 10 <= uVar27)) &&
        ((puVar34[-0xf4e] == '\x04' && (*(int *)(puVar34 + -0xf4d) == 0x6873656d)))) &&
       (1 < (int)(bVar36 - 5))) {
      lVar26 = *(long *)(puVar34 + -0x1010);
      lVar33 = (ulong)bVar25 * 0x7cc;
      *(ulong *)(puVar34 + -0xfc0) = (ulong)bVar25;
      puVar40 = (undefined8 *)(lVar26 + lVar33);
      *(long *)(puVar34 + -0x1000) = lVar33;
      *puVar40 = 0;
      *(undefined8 *)((long)puVar40 + 0x7c4) = 0;
      puVar22 = (undefined8 *)((ulong)(puVar40 + 1) & 0xfffffffffffffff8);
      for (uVar27 = (ulong)(((int)puVar40 -
                            (int)(undefined8 *)((ulong)(puVar40 + 1) & 0xfffffffffffffff8)) + 0x7ccU
                           >> 3); uVar27 != 0; uVar27 = uVar27 - 1) {
        *puVar22 = 0;
        puVar22 = puVar22 + (ulong)bVar50 * -2 + 1;
      }
      if (puVar34[-0xf49] == '\x05') {
        uVar18 = (uint)bVar25;
        *(uint *)(puVar34 + -4000) = (uint)bVar25;
        *(undefined4 *)(puVar34 + -0xfc8) = 0;
        *(undefined4 *)(puVar34 + -0xfd0) = 0;
        *(undefined4 *)(puVar34 + -0xfd8) = 0;
        *(undefined4 *)(puVar34 + -0xfe0) = 0;
        *(undefined4 *)(puVar34 + -0xfe8) = 0;
        *(undefined4 *)(puVar34 + -0xff0) = 0;
        *(ulong *)(puVar34 + -0xfa8) = (ulong)(byte)puVar34[-0xf48];
        *(long *)(puVar34 + -0xfb0) = (long)(int)(bVar36 - 5);
        *(undefined8 *)(puVar34 + -0xff8) = 0;
        *(FILE **)(puVar34 + -0x1008) = __stream;
        *(undefined4 *)(puVar34 + -0xfb8) = 0;
        uVar27 = 2;
LAB_00102b7d:
        if (*(ulong *)(puVar34 + -0xfa8) <= *(ulong *)(puVar34 + -0xff8)) goto LAB_00104c67;
        if (*(ulong *)(puVar34 + -0xfb0) < uVar27 + 3) goto switchD_00102beb_default;
        uVar35 = puVar34[uVar27 - 0xf48];
        uVar8 = CONCAT11(puVar34[uVar27 - 0xf47],uVar35);
        uVar49 = (ulong)CONCAT11(puVar34[uVar27 - 0xf47],uVar35);
        uVar46 = uVar27 + 3 + uVar49;
        if (*(ulong *)(puVar34 + -0xfb0) < uVar46) goto switchD_00102beb_default;
        switch(puVar34[uVar27 - 0xf49]) {
        case 1:
          if (uVar8 < 2) break;
          iVar16 = 1;
          *(undefined2 *)(lVar26 + 3 + (long)(int)uVar18 * 0x7cc) =
               *(undefined2 *)(puVar34 + (uVar27 - 0xf46));
LAB_00103974:
          *(long *)(puVar34 + -0xff8) = *(long *)(puVar34 + -0xff8) + 1;
          uVar27 = uVar46;
          goto LAB_00102b7d;
        case 2:
          if (uVar8 != 0) {
            bVar25 = puVar34[uVar27 - 0xf46];
            uVar49 = uVar27 + 4;
            if ((byte)(bVar25 - 1) < 6) {
              puVar34[(long)(int)uVar18 * 0x7cc + 0xaf] = bVar25;
              if (uVar27 + 6 <= uVar46) {
                *(uint *)(puVar34 + -0xf9c) = uVar18;
                uVar27 = 0;
                *(undefined1 **)(puVar34 + -0xfb8) = puVar34 + -0xf49;
                puVar22 = puVar40;
                while( true ) {
                  uVar31 = (ulong)(byte)puVar34[uVar49 - 0xf49];
                  lVar43 = uVar49 + 1;
                  if (0xe < (byte)(puVar34[uVar49 - 0xf49] - 1)) goto switchD_00102beb_default;
                  lVar45 = lVar43 + uVar31;
                  uVar49 = lVar45 + 1;
                  if (uVar46 < uVar49) goto switchD_00102beb_default;
                  lVar48 = *(long *)(puVar34 + -0xfb8);
                  *(undefined1 (*) [16])((long)puVar22 + 0xe) = (undefined1  [16])0x0;
                  puVar44 = (undefined1 *)(lVar43 + lVar48);
                  puVar38 = (undefined1 *)((long)puVar22 + 0xe);
                  for (; uVar31 != 0; uVar31 = uVar31 - 1) {
                    *puVar38 = *puVar44;
                    puVar44 = puVar44 + (ulong)bVar50 * -2 + 1;
                    puVar38 = puVar38 + (ulong)bVar50 * -2 + 1;
                  }
                  bVar36 = puVar34[lVar45 + -0xf49];
                  *(byte *)((long)puVar22 + 0x1e) = bVar36;
                  if (5 < bVar36) goto switchD_00102beb_default;
                  uVar27 = uVar27 + 1;
                  if (bVar25 <= uVar27) break;
                  puVar22 = (undefined8 *)((long)puVar22 + 0x14);
                  if (uVar46 < lVar45 + 3U) goto switchD_00102beb_default;
                }
                *(undefined4 *)(puVar34 + -0xfb8) = 1;
                uVar18 = *(uint *)(puVar34 + -0xf9c);
                goto LAB_00103974;
              }
            }
          }
          break;
        case 3:
          if ((uVar8 != 0) && (bVar25 = puVar34[uVar27 - 0xf46], (byte)(bVar25 - 1) < 6)) {
            uVar49 = uVar27 + 6;
            puVar34[(long)(int)uVar18 * 0x7cc + 0xae] = bVar25;
            if (uVar49 <= uVar46) {
              uVar27 = uVar27 + 4;
              puVar44 = (undefined1 *)(lVar26 + 0x9e + *(long *)(puVar34 + -0xfc0) * 0x7cc);
              uVar31 = 0;
              while( true ) {
                sVar9 = CONCAT11(puVar34[uVar27 - 0xf48],puVar34[uVar27 - 0xf49]);
                if ((0x5f < (ushort)(sVar9 - 1U)) ||
                   (uVar27 = (long)sVar9 + uVar49, uVar46 < uVar27)) goto switchD_00102beb_default;
                *(short *)((long)puVar40 + uVar31 * 2 + 0x86) = sVar9;
                uVar31 = uVar31 + 1;
                puVar38 = puVar34 + (uVar49 - 0xf49);
                puVar41 = puVar44;
                for (uVar28 = (ulong)(uint)(int)sVar9; uVar28 != 0; uVar28 = uVar28 - 1) {
                  *puVar41 = *puVar38;
                  puVar38 = puVar38 + (ulong)bVar50 * -2 + 1;
                  puVar41 = puVar41 + (ulong)bVar50 * -2 + 1;
                }
                if (bVar25 <= uVar31) break;
                uVar49 = uVar27 + 2;
                puVar44 = puVar44 + 0x60;
                if (uVar46 < uVar49) goto switchD_00102beb_default;
              }
              *(undefined4 *)(puVar34 + -0xff0) = 1;
              goto LAB_00103974;
            }
          }
          break;
        case 4:
          if (uVar8 != 0) {
            bVar25 = puVar34[uVar27 - 0xf46];
            if ((byte)(bVar25 - 1) < 4) {
              puVar34[(long)(int)uVar18 * 0x7cc + 0xb2] = bVar25;
              lVar43 = (ulong)bVar25 * 4;
              if (uVar27 + 4 + lVar43 <= uVar46) {
                puVar44 = puVar34 + (uVar27 - 0xf45);
                puVar38 = (undefined1 *)(lVar26 + 0x51e + lVar33);
                for (; lVar43 != 0; lVar43 = lVar43 + -1) {
                  *puVar38 = *puVar44;
                  puVar44 = puVar44 + (ulong)bVar50 * -2 + 1;
                  puVar38 = puVar38 + (ulong)bVar50 * -2 + 1;
                }
                uVar27 = 0;
                puVar22 = puVar40;
                do {
                  if (((2 < *(byte *)((long)puVar22 + 0x51e)) ||
                      (1 < *(byte *)((long)puVar22 + 0x51f))) || (2 < *(byte *)(puVar22 + 0xa4)))
                  goto switchD_00102beb_default;
                  uVar27 = uVar27 + 1;
                  puVar22 = (undefined8 *)((long)puVar22 + 4);
                } while (uVar27 < bVar25);
                *(undefined4 *)(puVar34 + -0xfe8) = 1;
                goto LAB_00103974;
              }
            }
          }
          break;
        case 5:
          if (uVar8 != 0) {
            bVar25 = puVar34[uVar27 - 0xf46];
            if ((byte)(bVar25 - 1) < 4) {
              puVar34[(long)(int)uVar18 * 0x7cc + 0xb3] = bVar25;
              lVar43 = (ulong)bVar25 * 4;
              if (uVar27 + 4 + lVar43 <= uVar46) {
                *(undefined4 *)(puVar34 + -0xfe0) = 1;
                puVar44 = puVar34 + (uVar27 - 0xf45);
                puVar38 = (undefined1 *)(lVar26 + 0x52e + lVar33);
                for (; lVar43 != 0; lVar43 = lVar43 + -1) {
                  *puVar38 = *puVar44;
                  puVar44 = puVar44 + (ulong)bVar50 * -2 + 1;
                  puVar38 = puVar38 + (ulong)bVar50 * -2 + 1;
                }
                goto LAB_00103974;
              }
            }
          }
          break;
        case 6:
          if ((ushort)(uVar8 - 1) < 0x100) {
            *(uint *)(puVar34 + -0xf9c) = uVar18;
            puVar34[(long)(int)uVar18 * 0x7cc + 0xb0] = uVar35;
            *(undefined8 *)(puVar34 + -0x1020) = 0x1039c0;
            memcpy((void *)(lVar26 + 0x54e + lVar33),puVar34 + (uVar27 - 0xf46),uVar49);
            *(undefined4 *)(puVar34 + -0xfd8) = 1;
            uVar18 = *(uint *)(puVar34 + -0xf9c);
            goto LAB_00103974;
          }
          break;
        case 7:
          if (uVar8 != 0) {
            bVar25 = puVar34[uVar27 - 0xf46];
            if ((bVar25 < 0x11) && (lVar43 = (ulong)bVar25 * 4, uVar27 + 4 + lVar43 <= uVar46)) {
              *(undefined4 *)(puVar34 + -0xfd0) = 1;
              puVar34[(long)(int)uVar18 * 0x7cc + 0xb1] = bVar25;
              puVar44 = puVar34 + (uVar27 - 0xf45);
              puVar38 = (undefined1 *)(lVar26 + 0x64e + lVar33);
              for (; lVar43 != 0; lVar43 = lVar43 + -1) {
                *puVar38 = *puVar44;
                puVar44 = puVar44 + (ulong)bVar50 * -2 + 1;
                puVar38 = puVar38 + (ulong)bVar50 * -2 + 1;
              }
              goto LAB_00103974;
            }
          }
          break;
        case 8:
          if (uVar8 != 0) {
            bVar25 = puVar34[uVar27 - 0xf46];
            if (((byte)(bVar25 - 1) < 4) &&
               (lVar43 = (ulong)bVar25 * 4, uVar27 + 4 + lVar43 <= uVar46)) {
              *(undefined4 *)(puVar34 + -0xfc8) = 1;
              puVar34[(long)(int)uVar18 * 0x7cc + 0xb4] = bVar25;
              puVar44 = puVar34 + (uVar27 - 0xf45);
              puVar38 = (undefined1 *)(lVar26 + 0x53e + lVar33);
              for (; lVar43 != 0; lVar43 = lVar43 + -1) {
                *puVar38 = *puVar44;
                puVar44 = puVar44 + (ulong)bVar50 * -2 + 1;
                puVar38 = puVar38 + (ulong)bVar50 * -2 + 1;
              }
              goto LAB_00103974;
            }
          }
        }
switchD_00102beb_default:
        __stream = *(FILE **)(puVar34 + -0x1008);
      }
    }
    goto LAB_001034f0;
  }
  *(undefined8 *)(puVar34 + -0x1020) = 0x10281f;
  iVar16 = strcmp(pcVar19,"inspect");
  if (iVar16 == 0) {
    if (__s2 != (char *)0x0) {
      *(undefined8 *)(puVar34 + -0x1020) = 0x102836;
      pcVar19 = strtok((char *)0x0," ");
      if (pcVar19 == (char *)0x0) {
        *(undefined8 *)(puVar34 + -0x1020) = 0x102c34;
        iVar16 = FUN_00101a30(__s2,puVar34 + -0xf91);
        if (iVar16 != 0) {
          bVar25 = puVar34[-0xf91];
          if (3 < bVar25) goto LAB_00102c06;
          puVar34[-0x1000] = bVar25;
          *(undefined8 *)(puVar34 + -0x1020) = 0x102c65;
          fprintf(__stream,"slot=%u\n",(ulong)bVar25);
          lVar43 = (long)(int)(uint)bVar25 * 0x7cc;
          *(long *)(puVar34 + -0x1008) = (long)(int)(uint)bVar25;
          bVar25 = puVar34[lVar43 + 0xa8];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102c98;
          fprintf(__stream,"loaded=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xa9];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102cb1;
          fprintf(__stream,"approved=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xaa];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102cca;
          fprintf(__stream,"seal_ready=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xab];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102ce3;
          fprintf(__stream,"audit_kind=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xac];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102cfc;
          fprintf(__stream,"declared_caps=0x%02x\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xad];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102d15;
          fprintf(__stream,"cap_mask=0x%02x\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xae];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102d2e;
          fprintf(__stream,"func_count=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xaf];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102d47;
          fprintf(__stream,"export_count=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xb2];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102d60;
          fprintf(__stream,"lane_count=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xb3];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102d79;
          fprintf(__stream,"account_count=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xb4];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102d92;
          fprintf(__stream,"route_count=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xb0];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102dab;
          fprintf(__stream,"blob_len=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0xb1];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102dc4;
          fprintf(__stream,"meter_count=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0x745];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102ddd;
          fprintf(__stream,"cache_warmed=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0x746];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102df6;
          fprintf(__stream,"cache_synced=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0x744];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102e0f;
          fprintf(__stream,"image_len=%u\n",(ulong)bVar25);
          uVar18 = *(uint *)(puVar34 + lVar43 + 0x788);
          *(undefined8 *)(puVar34 + -0x1020) = 0x102e27;
          fprintf(__stream,"profile_root=0x%08x\n",(ulong)uVar18);
          bVar25 = puVar34[lVar43 + 0x78d];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102e40;
          fprintf(__stream,"quote_ready=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0x78c];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102e59;
          fprintf(__stream,"quote_arena_len=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0x78f];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102e72;
          fprintf(__stream,"quote_loaded=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0x790];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102e8b;
          fprintf(__stream,"quote_writable=%u\n",(ulong)bVar25);
          uVar18 = *(uint *)(puVar34 + lVar43 + 0x7fc);
          *(undefined8 *)(puVar34 + -0x1020) = 0x102ea3;
          fprintf(__stream,"quote_root=0x%08x\n",(ulong)uVar18);
          bVar25 = puVar34[lVar43 + 0x801];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102ebc;
          fprintf(__stream,"attest_ready=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0x800];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102ed5;
          fprintf(__stream,"attest_arena_len=%u\n",(ulong)bVar25);
          bVar25 = puVar34[lVar43 + 0x803];
          *(undefined8 *)(puVar34 + -0x1020) = 0x102eee;
          fprintf(__stream,"attest_signers=0x%02x\n",(ulong)bVar25);
          uVar18 = *(uint *)(puVar34 + lVar43 + 0x870);
          pcVar19 = "attest_root=0x%08x\n";
          *(undefined8 *)(puVar34 + -0x1020) = 0x102f08;
          fprintf(__stream,"attest_root=0x%08x\n",(ulong)uVar18);
          lVar26 = *(long *)(puVar34 + -0x1010) + (ulong)(byte)puVar34[-0x1000] * 0x7cc;
          lVar33 = lVar26;
          for (uVar27 = 0; (uVar27 < (byte)puVar34[lVar43 + 0xaf] && (uVar27 != 6));
              uVar27 = uVar27 + 1) {
            pcVar19 = "export[%zu]=%s:%u\n";
            *(undefined8 *)(puVar34 + -0x1020) = 0x102f49;
            fprintf(__stream,"export[%zu]=%s:%u\n",uVar27,lVar33 + 0xe);
            lVar33 = lVar33 + 0x14;
          }
          lVar33 = *(long *)(puVar34 + -0x1008);
          lVar43 = lVar26;
          for (uVar27 = 0; (uVar27 < (byte)puVar34[lVar33 * 0x7cc + 0xb2] && (uVar27 != 4));
              uVar27 = uVar27 + 1) {
            bVar25 = *(byte *)(lVar43 + 0x51e);
            *(char **)(puVar34 + -0x1020) = pcVar19;
            pcVar19 = "decl_lane[%zu]=kind:%u role:%u acct:%u flags:0x%02x\n";
            *(ulong *)(puVar34 + -0x1028) = (ulong)*(byte *)(lVar43 + 0x521);
            bVar36 = *(byte *)(lVar43 + 0x51f);
            *(FILE **)(puVar34 + -0x1000) = __stream;
            *(undefined8 *)(puVar34 + -0x1030) = 0x102fe0;
            fprintf(__stream,"decl_lane[%zu]=kind:%u role:%u acct:%u flags:0x%02x\n",uVar27,
                    (ulong)bVar25,(ulong)bVar36);
            __stream = *(FILE **)(puVar34 + -0x1000);
            lVar43 = lVar43 + 4;
          }
          lVar33 = *(long *)(puVar34 + -0x1008);
          uVar27 = 0;
          while( true ) {
            if (((byte)puVar34[lVar33 * 0x7cc + 0xb4] <= uVar27) || (uVar27 == 4)) break;
            bVar25 = *(byte *)(lVar26 + 0x53e);
            *(ulong *)(puVar34 + -0x1020) = (ulong)(byte)puVar34[lVar33 * 0x7cc + 0xb4];
            *(ulong *)(puVar34 + -0x1028) = (ulong)*(byte *)(lVar26 + 0x541);
            *(undefined8 *)(puVar34 + -0x1030) = 0x10358a;
            fprintf(__stream,"route[%zu]=lane:%u acct:%u flags:0x%02x tag:0x%02x\n",uVar27,
                    (ulong)bVar25);
            lVar26 = lVar26 + 4;
            uVar27 = uVar27 + 1;
          }
          goto LAB_001027e0;
        }
      }
    }
    *(undefined8 *)(puVar34 + -0x1020) = 0x102858;
    fwrite("ERR usage inspect <slot>\n",1,0x19,__stream);
  }
  else {
    *(undefined8 *)(puVar34 + -0x1020) = 0x1028ca;
    iVar16 = strcmp(pcVar19,"warm");
    if (iVar16 == 0) {
      if ((__s2 != (char *)0x0) && (pcVar21 != (char *)0x0)) {
        *(undefined8 *)(puVar34 + -0x1020) = 0x1028e2;
        pcVar19 = strtok((char *)0x0," ");
        if (pcVar19 == (char *)0x0) {
          *(undefined8 *)(puVar34 + -0x1020) = 0x102bfe;
          iVar16 = FUN_00101a30(__s2,puVar34 + -0xf91);
          if (iVar16 == 0) goto LAB_00102c06;
          *(undefined8 *)(puVar34 + -0x1020) = 0x10326b;
          FUN_00101f20(__stream,*(undefined8 *)(puVar34 + -0x1010),puVar34[-0xf91],pcVar21);
          goto LAB_001027e0;
        }
      }
      *(undefined8 *)(puVar34 + -0x1020) = 0x102904;
      fwrite("ERR usage warm <slot> <hex_profile>\n",1,0x24,__stream);
    }
    else {
      *(undefined8 *)(puVar34 + -0x1020) = 0x102940;
      iVar16 = strcmp(pcVar19,"sync");
      if (iVar16 == 0) {
        if (__s2 != (char *)0x0) {
          *(undefined8 *)(puVar34 + -0x1020) = 0x102953;
          pcVar19 = strtok((char *)0x0," ");
          if (pcVar19 == (char *)0x0) {
            *(undefined8 *)(puVar34 + -0x1020) = 0x1031ea;
            iVar16 = FUN_00101a30(__s2,puVar34 + -0xf91);
            if (iVar16 != 0) {
              bVar25 = puVar34[-0xf91];
              if (bVar25 < 4) {
                uVar27 = (ulong)bVar25;
                lVar26 = (ulong)bVar25 * 0x7cc;
                if (((puVar34[lVar26 + 0xa8] == '\0') || (puVar34[lVar26 + 0xa9] == '\0')) ||
                   (puVar34[lVar26 + 0x745] == '\0')) {
                  *(undefined8 *)(puVar34 + -0x1020) = 0x10324e;
                  fwrite("ERR slot not synced\n",1,0x14,__stream);
                }
                else {
                  uVar18 = ((byte)puVar34[lVar26 + 0x744] ^ 0xc24cde8c) * 0x1000193 ^ 0x811c9dc5;
                  for (uVar46 = 0; uVar46 < (byte)puVar34[lVar26 + 0x744]; uVar46 = uVar46 + 1) {
                    uVar18 = (uVar18 ^ *(byte *)(*(long *)(puVar34 + -0x1010) + 0x6a0 + lVar26 +
                                                uVar46)) * 0x1000193;
                  }
                  lVar33 = (ulong)bVar25 * 0x7cc;
                  uVar18 = ((byte)puVar34[lVar33 + 0xb4] ^ uVar18 ^ 0x811c9dc5) * 0x1000193 ^
                           0x811c9dc5;
                  for (uVar46 = 0; uVar46 < (ulong)(byte)puVar34[lVar33 + 0xb1] << 2;
                      uVar46 = uVar46 + 1) {
                    uVar18 = (uVar18 ^ *(byte *)(*(long *)(puVar34 + -0x1010) + 0x64e + lVar26 +
                                                uVar46)) * 0x1000193;
                  }
                  lVar45 = (ulong)bVar25 * 0x7cc;
                  lVar33 = *(long *)(puVar34 + -0x1010);
                  *(uint *)(puVar34 + lVar45 + 0x788) = uVar18;
                  puVar34[lVar45 + 0x746] = 1;
                  puVar32 = (undefined4 *)(lVar33 + 0x6e4 + lVar26);
                  for (lVar43 = 0x1d; lVar43 != 0; lVar43 = lVar43 + -1) {
                    *puVar32 = 0;
                    puVar32 = puVar32 + (ulong)bVar50 * -2 + 1;
                  }
                  *(undefined8 *)(puVar34 + -0x1020) = 0x1036c2;
                  FUN_001017b0(lVar33 + lVar26);
                  uVar18 = *(uint *)(puVar34 + lVar45 + 0x788);
                  *(undefined8 *)(puVar34 + -0x1020) = 0x1036de;
                  fprintf(__stream,"OK synced slot %u profile_root=0x%08x\n",uVar27 & 0xffffffff,
                          (ulong)uVar18);
                }
                goto LAB_001027e0;
              }
              goto LAB_00102c06;
            }
          }
        }
        *(undefined8 *)(puVar34 + -0x1020) = 0x102975;
        fwrite("ERR usage sync <slot>\n",1,0x16,__stream);
      }
      else {
        *(undefined8 *)(puVar34 + -0x1020) = 0x102989;
        iVar16 = strcmp(pcVar19,"quote");
        if (iVar16 == 0) {
          if ((__s2 != (char *)0x0) && (pcVar21 != (char *)0x0)) {
            *(undefined8 *)(puVar34 + -0x1020) = 0x1029a5;
            pcVar19 = strtok((char *)0x0," ");
            if (pcVar19 == (char *)0x0) {
              *(undefined8 *)(puVar34 + -0x1020) = 0x103280;
              iVar16 = FUN_00101a30(__s2,puVar34 + -0xf91);
              if (iVar16 != 0) {
                bVar25 = puVar34[-0xf91];
                uVar27 = (ulong)bVar25;
                *(undefined8 *)(puVar34 + -0xf88) = 0;
                if (bVar25 < 4) {
                  *(uint *)(puVar34 + -0xfe8) = (uint)bVar25;
                  lVar26 = uVar27 * 0x7cc;
                  if (((puVar34[lVar26 + 0xa8] == '\0') || (puVar34[lVar26 + 0xa9] == '\0')) ||
                     (puVar34[lVar26 + 0x746] == '\0')) {
                    *(undefined8 *)(puVar34 + -0x1020) = 0x104db0;
                    fwrite("ERR slot not quotable\n",1,0x16,__stream);
                  }
                  else {
                    pbVar1 = puVar34 + -0xf58;
                    puVar34[-0x1008] = bVar25;
                    *(undefined8 *)(puVar34 + -0x1020) = 0x103307;
                    iVar16 = FUN_00101dd0(pcVar21,pbVar1,puVar34 + -0xf88,0x200);
                    if (iVar16 == 0) {
                      *(undefined8 *)(puVar34 + -0x1020) = 0x104d92;
                      fwrite("ERR bad receipt\n",1,0x10,__stream);
                    }
                    else {
                      lVar33 = (ulong)(byte)puVar34[-0x1008] * 0x7cc;
                      uVar46 = *(ulong *)(puVar34 + -0xf88);
                      lVar26 = *(long *)(puVar34 + -0x1010) + lVar33;
                      bVar25 = (char)*(undefined4 *)(puVar34 + -0xfe8) + 0xbU & 0x1f;
                      uVar18 = (uint)*(byte *)(lVar26 + 0x69c) * 0x7f4a7c15 ^
                               *(uint *)(puVar34 + 0x1ff0) ^ *(uint *)(lVar26 + 0x6e0) ^
                               (*(uint *)(lVar26 + 0x690) << bVar25 |
                               *(uint *)(lVar26 + 0x690) >> 0x20 - bVar25) ^ 0x51554f54;
                      for (pbVar30 = pbVar1; pbVar1 + uVar46 != pbVar30; pbVar30 = pbVar30 + 1) {
                        uVar18 = uVar18 * 0x19660d + 0x3c6ef35f;
                        *pbVar30 = *pbVar30 ^ (byte)(uVar18 >> 0x18);
                      }
                      uVar49 = 0;
                      puVar44 = puVar34 + -0xf59;
                      puVar32 = (undefined4 *)(*(long *)(puVar34 + -0x1010) + 0x6e4 + lVar33);
                      for (lVar43 = 0x1d; lVar43 != 0; lVar43 = lVar43 + -1) {
                        *puVar32 = 0;
                        puVar32 = puVar32 + (ulong)bVar50 * -2 + 1;
                      }
                      *(undefined8 *)(puVar34 + -0x1020) = 0x1033b1;
                      FUN_001017b0(lVar26);
                      iVar16 = 0;
                      *(undefined4 *)(puVar34 + -4000) = 0;
                      while( true ) {
                        if ((uVar46 <= uVar49) || (iVar16 == 0x23)) goto LAB_00104ed3;
                        uVar49 = uVar49 + 1;
                        bVar25 = puVar44[uVar49];
                        *(uint *)(puVar34 + -4000) =
                             *(uint *)(puVar34 + -4000) | (bVar25 & 0x7f) << ((byte)iVar16 & 0x1f);
                        if (-1 < (char)bVar25) break;
                        iVar16 = iVar16 + 7;
                      }
                      if (*(int *)(puVar34 + -4000) - 1U < 0x10) {
                        *(long *)(puVar34 + -0xfd0) = lVar26;
                        *(long *)(puVar34 + -0xfe0) = lVar33;
                        *(undefined4 *)(puVar34 + -0xff8) = 0;
                        *(long *)(puVar34 + -0x1000) = *(long *)(puVar34 + -0x1010) + 0x6ec + lVar33
                        ;
                        *(long *)(puVar34 + -0xfd8) = lVar33 + 0x744;
                        *(FILE **)(puVar34 + -0x1008) = __stream;
                        *(ulong *)(puVar34 + -0xff0) = uVar27 * 0x7cc;
                        goto LAB_00104e9c;
                      }
LAB_00104ed3:
                      *(undefined8 *)(puVar34 + -0x1020) = 0x104eec;
                      fwrite("ERR receipt header\n",1,0x13,__stream);
                    }
                  }
                  goto LAB_001027e0;
                }
              }
              goto LAB_00102c06;
            }
          }
          *(undefined8 *)(puVar34 + -0x1020) = 0x1029c7;
          fwrite("ERR usage quote <slot> <hex_receipt>\n",1,0x25,__stream);
          goto LAB_001027e0;
        }
        *(undefined8 *)(puVar34 + -0x1020) = 0x102ff9;
        iVar16 = strcmp(pcVar19,"attest");
        if (iVar16 == 0) {
          if ((__s2 != (char *)0x0) && (pcVar21 != (char *)0x0)) {
            *(undefined8 *)(puVar34 + -0x1020) = 0x103011;
            pcVar19 = strtok((char *)0x0," ");
            if (pcVar19 == (char *)0x0) {
              *(undefined8 *)(puVar34 + -0x1020) = 0x103765;
              iVar16 = FUN_00101a30(__s2,puVar34 + -0xf91);
              if (iVar16 != 0) {
                bVar25 = puVar34[-0xf91];
                *(undefined8 *)(puVar34 + -0xf88) = 0;
                if (bVar25 < 4) {
                  *(uint *)(puVar34 + -0xfe8) = (uint)bVar25;
                  lVar26 = (ulong)bVar25 * 0x7cc;
                  if ((((puVar34[lVar26 + 0xa8] == '\0') || (puVar34[lVar26 + 0xa9] == '\0')) ||
                      (puVar34[lVar26 + 0x746] == '\0')) || (puVar34[lVar26 + 0x78d] == '\0')) {
                    *(undefined8 *)(puVar34 + -0x1020) = 0x1040f3;
                    fwrite("ERR slot not attestable\n",1,0x18,__stream);
                  }
                  else {
                    pbVar1 = puVar34 + -0xf58;
                    *(ulong *)(puVar34 + -0x1008) = (ulong)bVar25;
                    *(undefined8 *)(puVar34 + -0x1020) = 0x1037f9;
                    iVar16 = FUN_00101dd0(pcVar21,pbVar1,puVar34 + -0xf88,0x200);
                    lVar26 = *(long *)(puVar34 + -0x1008);
                    if (iVar16 == 0) {
                      *(undefined8 *)(puVar34 + -0x1020) = 0x103a9a;
                      fwrite("ERR bad witness\n",1,0x10,__stream);
                    }
                    else {
                      uVar46 = (ulong)bVar25;
                      uVar27 = *(ulong *)(puVar34 + -0xf88);
                      lVar33 = *(long *)(puVar34 + -0x1010) + uVar46 * 0x7cc;
                      *(ulong *)(puVar34 + -0x1000) = uVar46 * 0x7cc;
                      bVar25 = *(byte *)(lVar33 + 0x6e8);
                      *(long *)(puVar34 + -0xff8) = lVar33;
                      uVar18 = *(uint *)(lVar33 + 0x754);
                      uVar37 = *(uint *)(lVar33 + 0x698);
                      *(uint *)(puVar34 + -0x1008) = uVar37;
                      bVar36 = (char)*(undefined4 *)(puVar34 + -0xfe8) + 0x11U & 0x1f;
                      uVar18 = (uint)bVar25 * 0x6c8e9cf5 ^ *(uint *)(puVar34 + 0x1ff0) ^ uVar18 ^
                               (uVar37 << bVar36 | uVar37 >> 0x20 - bVar36) ^ 0x41545453;
                      for (pbVar30 = pbVar1; pbVar1 + uVar27 != pbVar30; pbVar30 = pbVar30 + 1) {
                        uVar18 = uVar18 * 0x19660d + 0x3c6ef35f;
                        *pbVar30 = *pbVar30 ^ (byte)(uVar18 >> 0x18);
                      }
                      uVar49 = 0;
                      puVar44 = puVar34 + -0xf59;
                      *(undefined8 *)(puVar34 + -0x1020) = 0x10389a;
                      FUN_001017b0(*(undefined8 *)(puVar34 + -0xff8));
                      iVar16 = 0;
                      *(undefined4 *)(puVar34 + -0xff0) = 0;
                      while( true ) {
                        if ((uVar27 <= uVar49) || (iVar16 == 0x23)) goto LAB_00103afd;
                        uVar49 = uVar49 + 1;
                        bVar25 = puVar44[uVar49];
                        *(uint *)(puVar34 + -0xff0) =
                             *(uint *)(puVar34 + -0xff0) | (bVar25 & 0x7f) << ((byte)iVar16 & 0x1f);
                        if (-1 < (char)bVar25) break;
                        iVar16 = iVar16 + 7;
                      }
                      if (*(int *)(puVar34 + -0xff0) - 1U < 0x10) {
                        *(ulong *)(puVar34 + -0xfe0) = uVar46;
                        *(undefined4 *)(puVar34 + -4000) = 0;
                        *(FILE **)(puVar34 + -0x1008) = __stream;
                        lVar33 = *(long *)(puVar34 + -0x1010);
                        *(byte **)(puVar34 + -0xfd8) = pbVar1;
                        goto LAB_00103acb;
                      }
LAB_00103afd:
                      *(undefined8 *)(puVar34 + -0x1020) = 0x103b16;
                      fwrite("ERR witness header\n",1,0x13,__stream);
                    }
                  }
                  goto LAB_001027e0;
                }
              }
              goto LAB_00102c06;
            }
          }
          *(undefined8 *)(puVar34 + -0x1020) = 0x103033;
          fwrite("ERR usage attest <slot> <hex_witness>\n",1,0x26,__stream);
        }
        else {
          *(undefined8 *)(puVar34 + -0x1020) = 0x103047;
          iVar16 = strcmp(pcVar19,"bless");
          if (iVar16 == 0) {
            if (__s2 != (char *)0x0) {
              *(undefined8 *)(puVar34 + -0x1020) = 0x103062;
              pcVar19 = strtok((char *)0x0," ");
              if (pcVar19 == (char *)0x0) {
                *(undefined8 *)(puVar34 + -0x1020) = 0x10307b;
                iVar16 = FUN_00101a30(__s2,puVar34 + -0xf91);
                if (iVar16 != 0) {
                  bVar25 = puVar34[-0xf91];
                  if (3 < bVar25) goto LAB_00102c06;
                  uVar27 = (ulong)bVar25;
                  lVar26 = uVar27 * 0x7cc;
                  if ((((puVar34[lVar26 + 0xa8] != '\0') && (puVar34[lVar26 + 0xa9] != '\0')) &&
                      ((puVar34[lVar26 + 0x746] != '\0' &&
                       (((puVar34[lVar26 + 0x78d] != '\0' && (puVar34[lVar26 + 0x801] != '\0')) &&
                        (puVar34[lVar26 + 0xab] == '\x01')))))) &&
                     (puVar34[lVar26 + 0xad] == '\x01')) {
                    *(FILE **)(puVar34 + -0x1008) = __stream;
                    uVar46 = 0;
                    bVar36 = puVar34[lVar26 + 0xaf];
                    *(ulong *)(puVar34 + -0x1000) = uVar27;
                    pcVar19 = (char *)(*(long *)(puVar34 + -0x1010) + 0xe + uVar27 * 0x7cc);
LAB_0010313a:
                    if ((uVar46 != 6) && (uVar46 < bVar36)) {
                      *(undefined8 *)(puVar34 + -0x1020) = 0x10315c;
                      iVar16 = strcmp(pcVar19,"fallback");
                      if (iVar16 != 0) goto code_r0x00103164;
                      cVar6 = puVar34[0x1fdc];
                      __stream = *(FILE **)(puVar34 + -0x1008);
                      puVar44 = puVar34 + -0xf58;
                      lVar26 = *(long *)(puVar34 + -0x1000) * 0x7cc;
                      puVar34[0x1fdc] = cVar6 + '\x01';
                      lVar43 = 0;
                      lVar33 = *(long *)(puVar34 + -0x1010);
                      uVar15 = *(undefined4 *)(puVar34 + lVar26 + 0x7fc);
                      puVar34[lVar26 + 0xb5] = cVar6;
                      puVar34[lVar26 + 0xaa] = 1;
                      uVar7 = *(undefined4 *)(puVar34 + lVar26 + 0x870);
                      lVar26 = lVar33 + 0x6d0 + lVar26;
                      uVar10 = *(undefined4 *)(lVar26 + -0x40);
                      uVar11 = *(undefined4 *)(lVar26 + -0x3c);
                      uVar12 = *(undefined4 *)(lVar26 + -0x38);
                      uVar13 = *(undefined4 *)(lVar26 + 0x10);
                      *(ushort *)(puVar34 + -0xf58) = CONCAT11(cVar6,bVar25);
                      *(ulong *)(puVar34 + -0xf46) = CONCAT44(uVar7,uVar15);
                      uVar18 = *(uint *)(puVar34 + 0x1fd8) ^ 0xd259dc89;
                      *(undefined4 *)(puVar34 + -0xf56) = uVar10;
                      *(undefined4 *)(puVar34 + -0xf52) = uVar11;
                      *(undefined4 *)(puVar34 + -0xf4e) = uVar12;
                      *(undefined4 *)(puVar34 + -0xf4a) = uVar13;
                      do {
                        pbVar1 = puVar44 + lVar43;
                        lVar43 = lVar43 + 1;
                        uVar18 = (uVar18 ^ *pbVar1) * 0x1000193;
                      } while (lVar43 != 0x1a);
                      *(ushort *)(puVar34 + -0xf84) = CONCAT11(cVar6,bVar25);
                      *(undefined4 *)(puVar34 + -0xf88) = 0x4c414553;
                      *(undefined2 *)(puVar34 + -0xf82) = 0x101;
                      *(uint *)(puVar34 + -0xf68) = uVar18;
                      lVar26 = 0;
                      *(undefined4 *)(puVar34 + -0xf80) = uVar10;
                      *(undefined4 *)(puVar34 + -0xf7c) = uVar11;
                      *(undefined4 *)(puVar34 + -0xf78) = uVar12;
                      *(undefined4 *)(puVar34 + -0xf74) = uVar13;
                      *(ulong *)(puVar34 + -0xf70) = CONCAT44(uVar7,uVar15);
                      do {
                        *(ushort *)(puVar44 + lVar26 * 2) =
                             CONCAT11("0123456789abcdef"[(byte)puVar34[lVar26 + -0xf88] & 0xf],
                                      "0123456789abcdef"[(byte)puVar34[lVar26 + -0xf88] >> 4]);
                        lVar26 = lVar26 + 1;
                      } while (lVar26 != 0x24);
                      puVar34[-0xf10] = 0;
                      *(undefined8 *)(puVar34 + -0x1020) = 0x1049b2;
                      fprintf(__stream,"SEAL %s\n",puVar44);
                      goto LAB_001027e0;
                    }
                    __stream = *(FILE **)(puVar34 + -0x1008);
                  }
                  *(undefined8 *)(puVar34 + -0x1020) = 0x104d56;
                  fwrite("ERR slot not blessable\n",1,0x17,__stream);
                  goto LAB_001027e0;
                }
              }
            }
            *(undefined8 *)(puVar34 + -0x1020) = 0x103183;
            fwrite("ERR usage bless <slot>\n",1,0x17,__stream);
          }
          else {
            *(undefined8 *)(puVar34 + -0x1020) = 0x103197;
            iVar16 = strcmp(pcVar19,"activate");
            if (iVar16 == 0) {
              if ((__s2 != (char *)0x0) && (pcVar21 != (char *)0x0)) {
                *(undefined8 *)(puVar34 + -0x1020) = 0x1031b3;
                pcVar19 = strtok((char *)0x0," ");
                if (pcVar19 == (char *)0x0) {
                  *(undefined8 *)(puVar34 + -0x1020) = 0x104661;
                  iVar16 = FUN_00101a30(__s2,puVar34 + -0xf91);
                  if (iVar16 != 0) {
                    bVar25 = puVar34[-0xf91];
                    *(undefined8 *)(puVar34 + -0xf90) = 0;
                    if (bVar25 < 4) {
                      *(undefined8 *)(puVar34 + -0x1020) = 0x1046a5;
                      iVar16 = FUN_00101dd0(pcVar21,puVar34 + -0xf58,puVar34 + -0xf90,0x40);
                      if (iVar16 == 0) {
                        *(undefined8 *)(puVar34 + -0x1020) = 0x104d74;
                        fwrite("ERR bad seal\n",1,0xd,__stream);
                      }
                      else {
                        if (((((((*(long *)(puVar34 + -0xf90) == 0x24) &&
                                (*(int *)(puVar34 + -0xf58) == 0x4c414553)) &&
                               (bVar25 == puVar34[-0xf54])) &&
                              ((lVar26 = (ulong)bVar25 * 0x7cc, puVar34[lVar26 + 0xa8] != '\0' &&
                               (puVar34[lVar26 + 0xa9] != '\0')))) &&
                             ((puVar34[lVar26 + 0x746] != '\0' &&
                              ((puVar34[lVar26 + 0x78d] != '\0' && (puVar34[lVar26 + 0x801] != '\0')
                               ))))) && (puVar34[-0xf52] == puVar34[lVar26 + 0xab])) &&
                           (puVar34[-0xf51] == puVar34[lVar26 + 0xad])) {
                          auVar3 = *(undefined1 (*) [16])(puVar34 + -0xf50);
                          uVar2 = *(undefined8 *)(puVar34 + -0xf40);
                          if (*(int *)(puVar34 + lVar26 + 0x738) == auVar3._0_4_) {
                            if ((((*(int *)(puVar34 + lVar26 + 0x73c) == auVar3._4_4_) &&
                                 (*(int *)(puVar34 + lVar26 + 0x740) == auVar3._8_4_)) &&
                                (*(int *)(puVar34 + lVar26 + 0x788) == auVar3._12_4_)) &&
                               ((*(int *)(puVar34 + lVar26 + 0x7fc) == (int)uVar2 &&
                                (*(int *)(puVar34 + lVar26 + 0x870) == (int)((ulong)uVar2 >> 0x20)))
                               )) {
                              lVar26 = 0;
                              *(undefined1 (*) [16])(puVar34 + -0xf86) = auVar3;
                              *(undefined8 *)(puVar34 + -0xf76) = uVar2;
                              *(ushort *)(puVar34 + -0xf88) = CONCAT11(puVar34[-0xf53],bVar25);
                              uVar18 = *(uint *)(puVar34 + 0x1fd8) ^ 0xd259dc89;
                              do {
                                lVar33 = lVar26 + -0xf88;
                                lVar26 = lVar26 + 1;
                                uVar18 = (uVar18 ^ (byte)puVar34[lVar33]) * 0x1000193;
                              } while (lVar26 != 0x1a);
                              if (*(uint *)(puVar34 + -0xf38) == uVar18) {
                                *(uint *)(puVar34 + 0x1fe0) = (uint)bVar25;
                                *(undefined8 *)(puVar34 + -0x1020) = 0x104864;
                                fprintf(__stream,"OK active slot %u\n",(ulong)(uint)bVar25);
                                goto LAB_001027e0;
                              }
                            }
                          }
                        }
                        *(undefined8 *)(puVar34 + -0x1020) = 0x1049d0;
                        fwrite("ERR seal reject\n",1,0x10,__stream);
                      }
                      goto LAB_001027e0;
                    }
                  }
                  goto LAB_00102c06;
                }
              }
              *(undefined8 *)(puVar34 + -0x1020) = 0x1031d5;
              fwrite("ERR usage activate <slot> <sealhex>\n",1,0x24,__stream);
            }
            else {
              *(undefined8 *)(puVar34 + -0x1020) = 0x1033fb;
              iVar16 = strcmp(pcVar19,"invoke");
              if (iVar16 == 0) {
                if (__s2 != (char *)0x0) {
                  *(undefined8 *)(puVar34 + -0x1020) = 0x103412;
                  pcVar19 = strtok((char *)0x0," ");
                  if (pcVar19 == (char *)0x0) {
                    uVar18 = *(uint *)(puVar34 + 0x1fe0);
                    if (uVar18 < 4) {
                      lVar26 = (long)(int)uVar18 * 0x7cc;
                      *(long *)(puVar34 + -0x1008) = (long)(int)uVar18;
                      bVar25 = puVar34[lVar26 + 0xaf];
                      *(long *)(puVar34 + -0x1000) = lVar26;
                      pcVar19 = (char *)(*(long *)(puVar34 + -0x1010) + 0xe + lVar26);
                      for (uVar27 = 0; (uVar27 != 6 && (uVar27 < bVar25)); uVar27 = uVar27 + 1) {
                        *(undefined8 *)(puVar34 + -0x1020) = 0x103747;
                        iVar16 = strncmp(pcVar19,__s2,0x10);
                        if (iVar16 == 0) {
                          lVar26 = *(long *)(puVar34 + -0x1000);
                          bVar25 = puVar34[uVar27 * 0x14 + *(long *)(puVar34 + -0x1008) * 0x7cc +
                                           0xc6];
                          if ((byte)puVar34[*(long *)(puVar34 + -0x1008) * 0x7cc + 0xae] <= bVar25)
                          goto switchD_0010416a_caseD_103a63;
                          *(char **)(puVar34 + -0xff8) = __s2;
                          iVar16 = 0;
                          *(long *)(puVar34 + -0x1000) = *(long *)(puVar34 + -0x1010) + lVar26;
                          lVar26 = lVar26 + 0x2de + (ulong)bVar25 * 0x60 +
                                   *(long *)(puVar34 + -0x1010);
                          uVar46 = (ulong)*(ushort *)
                                           (puVar34 +
                                           ((ulong)bVar25 + 0x48 +
                                           *(long *)(puVar34 + -0x1008) * 0x3e6) * 2 + 0xaa);
                          uVar27 = 0;
                          goto LAB_0010413f;
                        }
                        pcVar19 = pcVar19 + 0x14;
                      }
                      *(undefined8 *)(puVar34 + -0x1020) = 0x1038ee;
                      fwrite("ERR missing export\n",1,0x13,__stream);
                    }
                    else {
                      *(undefined8 *)(puVar34 + -0x1020) = 0x10390c;
                      fwrite("ERR no active slot\n",1,0x13,__stream);
                    }
                    goto LAB_001027e0;
                  }
                }
                *(undefined8 *)(puVar34 + -0x1020) = 0x103434;
                fwrite("ERR usage invoke <export_name>\n",1,0x1f,__stream);
              }
              else {
                *(undefined8 *)(puVar34 + -0x1020) = 0x1035bb;
                iVar16 = strcmp(pcVar19,"flag");
                if (iVar16 != 0) {
                  *(undefined8 *)(puVar34 + -0x1020) = 0x1039fc;
                  iVar16 = strcmp(pcVar19,"quit");
                  if (iVar16 != 0) {
                    *(undefined8 *)(puVar34 + -0x1020) = 0x103a13;
                    iVar16 = strcmp(pcVar19,"exit");
                    if (iVar16 != 0) {
                      *(undefined8 *)(puVar34 + -0x1020) = 0x103a34;
                      fwrite("ERR unknown command\n",1,0x14,__stream);
                      goto LAB_001027e0;
                    }
                  }
                  *(undefined8 *)(puVar34 + -0x1020) = 0x102922;
                  fwrite(&DAT_0010674a,1,4,__stream);
                  goto LAB_00102922;
                }
                if (*(int *)(puVar34 + 0x1fe4) == 0) {
                  *(undefined8 *)(puVar34 + -0x1020) = 0x1039e8;
                  fwrite("ERR vault still sealed\n",1,0x17,__stream);
                }
                else {
                  *(undefined8 *)(puVar34 + -0x1020) = 0x1035e7;
                  fprintf(__stream,"%s\n",&DAT_00108040);
                }
              }
            }
          }
        }
      }
    }
  }
LAB_001027e0:
  *(undefined8 *)(puVar34 + -0x1020) = 0x1027f9;
  fwrite(&DAT_001061dc,1,2,__stream);
  goto LAB_001026e0;
LAB_00104c67:
  __stream = *(FILE **)(puVar34 + -0x1008);
  if (((((((iVar16 == 1 && *(int *)(puVar34 + -0xfb8) == 1) && *(int *)(puVar34 + -0xff0) == 1) &&
         *(int *)(puVar34 + -0xfe8) == 1) && *(int *)(puVar34 + -0xfe0) == 1) &&
       *(int *)(puVar34 + -0xfd8) == 1) && *(int *)(puVar34 + -0xfd0) == 1) &&
      *(int *)(puVar34 + -0xfc8) == 1) {
    lVar26 = (long)*(int *)(puVar34 + -4000);
    bVar25 = puVar34[lVar26 * 0x7cc + 0xb4];
    puVar34[-0xff8] = bVar25;
    if ((bVar25 != 0) && (bVar36 = puVar34[lVar26 * 0x7cc + 0xb2], bVar36 != 0)) {
      uVar27 = 0;
      puVar22 = puVar40;
      do {
        if ((bVar36 <= *(byte *)((long)puVar22 + 0x53e)) || (2 < *(byte *)((long)puVar22 + 0x53f)))
        goto LAB_001034f0;
        uVar27 = uVar27 + 1;
        puVar22 = (undefined8 *)((long)puVar22 + 4);
      } while (uVar27 < bVar25);
      lVar33 = *(long *)(puVar34 + -0x1010);
      bVar24 = 0;
      puVar34[lVar26 * 0x7cc + 0xa8] = 1;
      bVar25 = puVar34[lVar26 * 0x7cc + 0xae];
      *(long *)(puVar34 + -0xff0) = *(long *)(puVar34 + -0xfc0) * 0x7cc;
      lVar33 = *(long *)(puVar34 + -0xfc0) * 0x7cc + lVar33;
      *(long *)(puVar34 + -0xfe8) = lVar33;
      for (uVar27 = 0; (uVar15 = 0, puVar22 = puVar40, uVar27 < bVar25 && (uVar27 != 6));
          uVar27 = uVar27 + 1) {
        uVar49 = (ulong)*(ushort *)((long)puVar40 + uVar27 * 2 + 0x86);
        *(FILE **)(puVar34 + -0x1008) = __stream;
        uVar46 = 0;
        while (uVar46 < uVar49) {
          uVar31 = uVar46 + 1;
          if (0x31 < *(byte *)(uVar46 + 0x9e + lVar33)) {
switchD_00104e45_caseD_104f97:
            __stream = *(FILE **)(puVar34 + -0x1008);
            bVar24 = 0xff;
            goto LAB_00104fa1;
          }
          switch((long)&switchD_00104e45::switchdataD_00106adc +
                 (long)(int)(&switchD_00104e45::switchdataD_00106adc)
                            [*(byte *)(lVar33 + 0x9d + uVar31)]) {
          case 0x104ef1:
            if (uVar31 < uVar49) {
              if ((byte)puVar34[uVar46 + uVar27 * 0x60 + lVar26 * 0x7cc + 0x147] <
                  (byte)puVar34[-0xff8]) {
                if ((byte)puVar34[((ulong)(byte)puVar34[uVar46 + uVar27 * 0x60 + lVar26 * 0x7cc +
                                                                 0x147] + 0x14c + lVar26 * 499) * 4
                                  + 0xb6] < bVar36) {
                  cVar6 = puVar34[(lVar26 * 499 + 0x144 +
                                  (ulong)(byte)puVar34[((ulong)(byte)puVar34[uVar46 + uVar27 * 0x60
                                                                                      + lVar26 *
                                                  0x7cc + 0x147] + 0x14c + lVar26 * 499) * 4 + 0xb6]
                                  ) * 4 + 0xb6];
                  goto joined_r0x00104f5a;
                }
              }
LAB_0010527e:
              __stream = *(FILE **)(puVar34 + -0x1008);
              puVar34[lVar26 * 0x7cc + 0xad] = 0xff;
              goto LAB_00104fc2;
            }
            goto switchD_00104e45_caseD_104f85;
          case 0x104f7c:
            if (uVar49 <= uVar31) goto switchD_00104e45_caseD_104f85;
            uVar46 = uVar46 + 2;
            break;
          case 0x104f85:
            goto switchD_00104e45_caseD_104f85;
          case 0x104f97:
            goto switchD_00104e45_caseD_104f97;
          case 0x105221:
            if (uVar49 <= uVar31) goto switchD_00104e45_caseD_104f85;
            if (bVar36 <= (byte)puVar34[uVar46 + uVar27 * 0x60 + lVar26 * 0x7cc + 0x147])
            goto LAB_0010527e;
            cVar6 = puVar34[((ulong)(byte)puVar34[uVar46 + uVar27 * 0x60 + lVar26 * 0x7cc + 0x147] +
                             0x144 + lVar26 * 499) * 4 + 0xb6];
joined_r0x00104f5a:
            if (cVar6 == '\0') {
              uVar46 = uVar46 + 2;
              bVar24 = bVar24 | 1;
            }
            else {
              uVar46 = uVar46 + 2;
              if (cVar6 == '\x01') {
                bVar24 = bVar24 | 2;
              }
              else {
                bVar24 = bVar24 | (cVar6 == '\x02') << 2;
              }
            }
            break;
          case 0x1055bb:
            uVar46 = uVar31;
          }
        }
switchD_00104e45_caseD_104f85:
        __stream = *(FILE **)(puVar34 + -0x1008);
        lVar33 = lVar33 + 0x60;
      }
LAB_00104fa1:
      lVar33 = lVar26 * 0x7cc;
      puVar34[lVar33 + 0xad] = bVar24;
      if ((puVar34[lVar33 + 0xab] == '\x01') && (bVar24 == 1)) {
        bVar25 = puVar34[lVar33 + 0xaf];
        *(undefined8 **)(puVar34 + -0x1008) = puVar40;
        *(long *)(puVar34 + -0xff8) = lVar26;
        pcVar19 = (char *)(*(long *)(puVar34 + -0x1010) + 0xe + *(long *)(puVar34 + -0xff0));
        for (uVar27 = 0; (uVar27 != 6 && (uVar27 < bVar25)); uVar27 = uVar27 + 1) {
          *(undefined4 *)(puVar34 + -0xfe0) = uVar15;
          *(undefined8 *)(puVar34 + -0x1020) = 0x1051ea;
          iVar16 = strcmp(pcVar19,"fallback");
          if (iVar16 == 0) {
            lVar26 = *(long *)(puVar34 + -0xff8);
            uVar15 = 1;
            puVar22 = *(undefined8 **)(puVar34 + -0x1008);
            goto LAB_00104fc2;
          }
          uVar15 = *(undefined4 *)(puVar34 + -0xfe0);
          pcVar19 = pcVar19 + 0x14;
        }
        lVar26 = *(long *)(puVar34 + -0xff8);
        puVar22 = *(undefined8 **)(puVar34 + -0x1008);
      }
LAB_00104fc2:
      puVar34[lVar26 * 0x7cc + 0xa9] = (char)uVar15;
      *(long *)(puVar34 + -0x1008) = lVar26 * 0x7cc;
      *(undefined8 *)(puVar34 + -0x1020) = 0x104fde;
      uVar18 = FUN_00101b40();
      uVar18 = (((byte)puVar34[*(long *)(puVar34 + -0x1008) + 0xac] ^ uVar18 ^ 0x811c9dc5) *
                0x1000193 ^ (uint)(byte)puVar34[*(long *)(puVar34 + -0x1008) + 0xb0] ^ 0x811c9dc5) *
               0x1000193 ^ 0x811c9dc5;
      for (uVar27 = 0; uVar27 < (byte)puVar34[*(long *)(puVar34 + -0x1008) + 0xb0];
          uVar27 = uVar27 + 1) {
        uVar18 = (uVar18 ^ *(byte *)(*(long *)(puVar34 + -0x1010) + 0x54e +
                                     *(long *)(puVar34 + -0x1000) + uVar27)) * 0x1000193;
      }
      uVar18 = ((byte)puVar34[lVar26 * 0x7cc + 0xb1] ^ uVar18 ^ 0x811c9dc5) * 0x1000193 ^ 0x811c9dc5
      ;
      for (uVar27 = 0; uVar27 < (ulong)(byte)puVar34[lVar26 * 0x7cc + 0xb1] << 2;
          uVar27 = uVar27 + 1) {
        uVar18 = (uVar18 ^ *(byte *)(*(long *)(puVar34 + -0x1010) + 0x64e +
                                     *(long *)(puVar34 + -0x1000) + uVar27)) * 0x1000193;
      }
      *(uint *)(puVar34 + lVar26 * 0x7cc + 0x738) = uVar18;
      *(long *)(puVar34 + -0x1008) = lVar26 * 0x7cc;
      *(undefined8 *)(puVar34 + -0x1020) = 0x1050b2;
      uVar15 = FUN_00101b40(puVar40);
      lVar33 = *(long *)(puVar34 + -0xff0);
      lVar43 = 0;
      *(undefined4 *)(puVar34 + *(long *)(puVar34 + -0x1008) + 0x73c) = uVar15;
      puVar32 = (undefined4 *)(*(long *)(puVar34 + -0x1010) + 0x2de + lVar33);
      puVar23 = puVar32;
      do {
        lVar43 = lVar43 + 1;
        *(undefined2 *)((long)puVar22 + 0x92) = *(undefined2 *)((long)puVar22 + 0x86);
        puVar39 = puVar23 + -0x90;
        puVar42 = puVar23;
        for (lVar33 = 0x18; lVar33 != 0; lVar33 = lVar33 + -1) {
          *puVar42 = *puVar39;
          puVar39 = puVar39 + (ulong)bVar50 * -2 + 1;
          puVar42 = puVar42 + (ulong)bVar50 * -2 + 1;
        }
        puVar23 = puVar23 + 0x18;
        puVar22 = (undefined8 *)((long)puVar22 + 2);
      } while (lVar43 != 6);
      lVar33 = *(long *)(puVar34 + -0xfe8);
      uVar18 = ((byte)puVar34[lVar26 * 0x7cc + 0xae] ^ 0xc444d980) * 0x1000193;
      for (uVar27 = 0; (uVar27 < (byte)puVar34[lVar26 * 0x7cc + 0xae] && (uVar27 != 6));
          uVar27 = uVar27 + 1) {
        uVar18 = ((uint)*(byte *)(lVar33 + 0x93) ^
                 (*(byte *)(lVar33 + 0x92) ^ uVar18 ^ 0x811c9dc5) * 0x1000193) * 0x1000193 ^
                 0x811c9dc5;
        for (uVar46 = 0; uVar46 < *(ushort *)((long)puVar40 + uVar27 * 2 + 0x92);
            uVar46 = uVar46 + 1) {
          uVar18 = (uVar18 ^ *(byte *)((long)puVar32 + uVar46)) * 0x1000193;
        }
        lVar33 = lVar33 + 2;
        puVar32 = puVar32 + 0x18;
      }
      lVar33 = *(long *)(puVar34 + -0x1000);
      lVar43 = *(long *)(puVar34 + -0x1010);
      *(uint *)(puVar34 + lVar26 * 0x7cc + 0x740) = uVar18;
      puVar32 = (undefined4 *)(lVar43 + 0x69c + lVar33);
      for (lVar26 = 0x12; lVar26 != 0; lVar26 = lVar26 + -1) {
        *puVar32 = 0;
        puVar32 = puVar32 + (ulong)bVar50 * -2 + 1;
      }
      puVar32 = (undefined4 *)(lVar43 + 0x6e4 + lVar33);
      for (lVar26 = 0x1d; lVar26 != 0; lVar26 = lVar26 + -1) {
        *puVar32 = 0;
        puVar32 = puVar32 + (ulong)bVar50 * -2 + 1;
      }
      *(undefined8 *)(puVar34 + -0x1020) = 0x10560a;
      FUN_001017b0(puVar40);
      *(undefined8 *)(puVar34 + -0x1020) = 0x10561f;
      fprintf(__stream,"OK uploaded slot %u\n",(ulong)*(uint *)(puVar34 + -4000));
      goto LAB_001027e0;
    }
  }
LAB_001034f0:
  *(undefined8 *)(puVar34 + -0x1020) = 0x103509;
  fwrite("ERR parse failed\n",1,0x11,__stream);
  goto LAB_001027e0;
LAB_0010413f:
  uVar49 = uVar27;
  if (uVar49 < uVar46) {
    uVar27 = uVar49 + 1;
    if (0x31 < *(byte *)(lVar26 + uVar49)) goto switchD_0010416a_caseD_103a63;
    switch((long)&switchD_0010416a::switchdataD_00106a14 +
           (long)(int)(&switchD_0010416a::switchdataD_00106a14)[*(byte *)(lVar26 + uVar49)]) {
    case 0x103a63:
      goto switchD_0010416a_caseD_103a63;
    case 0x1043ef:
      if (1 < iVar16) goto code_r0x001043f8;
      goto switchD_0010416a_caseD_103a63;
    case 0x104426:
      if ((uVar46 <= uVar27) || (iVar16 < 1)) goto switchD_0010416a_caseD_103a63;
      iVar16 = iVar16 + -1;
      uVar49 = uVar49 + 2;
      bVar25 = *(byte *)(lVar26 + uVar27);
      iVar17 = (int)(char)bVar25;
      uVar27 = uVar49;
      if (*(int *)(puVar34 + (long)iVar16 * 4 + -0xf58) == 0) {
        if ((char)bVar25 < '\0') {
          if (uVar49 < (ulong)(long)-iVar17) goto switchD_0010416a_caseD_103a63;
        }
        else if (bVar25 == 0) {
          iVar17 = 0;
        }
        else if (uVar46 < bVar25 + uVar49) goto switchD_0010416a_caseD_103a63;
        uVar27 = (long)(iVar17 + (int)uVar49);
      }
      goto LAB_0010413f;
    case 0x10447b:
      if (uVar46 <= uVar27) goto switchD_0010416a_caseD_103a63;
      bVar25 = *(byte *)(lVar26 + uVar27);
      if ((byte)puVar34[*(long *)(puVar34 + -0x1008) * 0x7cc + 0xb4] <= bVar25)
      goto switchD_0010416a_caseD_103a63;
      if (0 < iVar16) {
        iVar16 = iVar16 + -1;
      }
      *(uint *)(puVar34 + -4000) = (uint)bVar25;
      *(long *)(puVar34 + -0xff0) = *(long *)(puVar34 + -0x1008) * 499;
      *(undefined8 *)(puVar34 + -0x1020) = 0x1044ec;
      iVar17 = FUN_00101a80(__stream,*(long *)(puVar34 + -0x1010),*(undefined8 *)(puVar34 + -0x1000)
                            ,*(long *)(puVar34 + -0x1010) +
                             (*(long *)(puVar34 + -0x1008) * 499 + 0x1ee + (ulong)bVar25) * 4);
      if (iVar17 < 0) goto switchD_0010416a_caseD_103a63;
      cVar6 = puVar34[(*(long *)(puVar34 + -0xff0) + 0x1ec + (long)*(int *)(puVar34 + -4000)) * 4 +
                      0xb0];
      break;
    case 0x10454b:
      if (uVar46 <= uVar27) goto switchD_0010416a_caseD_103a63;
      bVar25 = *(byte *)(lVar26 + uVar27);
      if ((byte)puVar34[*(long *)(puVar34 + -0x1008) * 0x7cc + 0xb2] <= bVar25)
      goto switchD_0010416a_caseD_103a63;
      if (0 < iVar16) {
        iVar16 = iVar16 + -1;
      }
      *(uint *)(puVar34 + -4000) = (uint)bVar25;
      *(long *)(puVar34 + -0xff0) = *(long *)(puVar34 + -0x1008) * 499;
      *(undefined8 *)(puVar34 + -0x1020) = 0x1045bb;
      iVar17 = FUN_00101a80(__stream,*(long *)(puVar34 + -0x1010),*(undefined8 *)(puVar34 + -0x1000)
                            ,*(long *)(puVar34 + -0x1010) + 0x51e +
                             ((ulong)bVar25 + *(long *)(puVar34 + -0x1008) * 499) * 4);
      if (iVar17 < 0) goto switchD_0010416a_caseD_103a63;
      cVar6 = puVar34[(*(long *)(puVar34 + -0xff0) + 0x144 + (long)*(int *)(puVar34 + -4000)) * 4 +
                      0xb6];
      break;
    case 0x1045e8:
      if (0x1f < iVar16) goto switchD_0010416a_caseD_103a63;
      lVar33 = (long)iVar16;
      iVar16 = iVar16 + 1;
      *(undefined4 *)(puVar34 + lVar33 * 4 + -0xf58) = 1;
      goto LAB_0010413f;
    case 0x10460a:
      if ((uVar46 <= uVar27) || (0x1f < iVar16)) goto switchD_0010416a_caseD_103a63;
      lVar33 = (long)iVar16;
      iVar16 = iVar16 + 1;
      *(uint *)(puVar34 + lVar33 * 4 + -0xf58) = (uint)*(byte *)(lVar26 + uVar27);
      uVar27 = uVar49 + 2;
      goto LAB_0010413f;
    case 0x104636:
      goto switchD_0010416a_caseD_104636;
    }
    uVar27 = uVar49 + 2;
    if (cVar6 == '\0') {
      if (0x1f < iVar16) goto switchD_0010416a_caseD_103a63;
      lVar33 = (long)iVar16;
      iVar16 = iVar16 + 1;
      *(int *)(puVar34 + lVar33 * 4 + -0xf58) = iVar17;
      uVar27 = uVar49 + 2;
    }
    goto LAB_0010413f;
  }
  goto switchD_0010416a_caseD_104636;
code_r0x001043f8:
  iVar17 = iVar16 + -2;
  iVar16 = iVar16 + -1;
  *(uint *)(puVar34 + (long)iVar17 * 4 + -0xf58) =
       (uint)(*(int *)(puVar34 + (long)iVar17 * 4 + -0xf58) ==
             *(int *)(puVar34 + (long)iVar16 * 4 + -0xf58));
  goto LAB_0010413f;
switchD_0010416a_caseD_103a63:
  *(undefined8 *)(puVar34 + -0x1020) = 0x103a7c;
  fwrite("ERR invoke fault\n",1,0x11,__stream);
  goto LAB_001027e0;
switchD_0010416a_caseD_104636:
  *(undefined8 *)(puVar34 + -0x1020) = 0x10464c;
  fprintf(__stream,"OK invoked %s\n",*(undefined8 *)(puVar34 + -0xff8));
  goto LAB_001027e0;
code_r0x00103164:
  uVar46 = uVar46 + 1;
  pcVar19 = pcVar19 + 0x14;
  goto LAB_0010313a;
LAB_00103acb:
  do {
    iVar16 = 0;
    uVar31 = 0;
    uVar46 = uVar49;
    while( true ) {
      if ((iVar16 == 0x23) || (uVar27 <= uVar46)) {
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x103b57;
        fwrite("ERR witness decode\n",1,0x13,__stream);
        goto LAB_001027e0;
      }
      uVar49 = uVar46 + 1;
      uVar18 = (uint)uVar31 | ((byte)puVar44[uVar49] & 0x7f) << ((byte)iVar16 & 0x1f);
      uVar31 = (ulong)uVar18;
      if (-1 < (char)puVar44[uVar49]) break;
      iVar16 = iVar16 + 7;
      uVar46 = uVar49;
    }
    switch(uVar18) {
    case 0:
      uVar46 = uVar31;
      while( true ) {
        if (((int)uVar31 == 0x23) || (uVar27 <= uVar49)) goto LAB_00103e8e;
        uVar49 = uVar49 + 1;
        uVar18 = (uint)uVar46 | ((byte)puVar44[uVar49] & 0x7f) << ((byte)uVar31 & 0x1f);
        uVar46 = (ulong)uVar18;
        if (-1 < (char)puVar44[uVar49]) break;
        uVar31 = (ulong)((int)uVar31 + 7);
      }
      if (uVar27 < uVar46 + uVar49) {
LAB_00103e8e:
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x103eac;
        fwrite("ERR arena add\n",1,0xe,__stream);
        goto LAB_001027e0;
      }
      *(ulong *)(puVar34 + -0xfc0) = uVar46 + uVar49;
      *(uint *)(puVar34 + -0xfd0) = uVar18;
      bVar25 = puVar34[lVar26 * 0x7cc + 0x800];
      *(long *)(puVar34 + -0xfc8) = lVar26 * 0x7cc;
      if (0x40 - bVar25 < uVar18) {
LAB_00103ed4:
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x103ef2;
        fwrite("ERR arena reject\n",1,0x11,__stream);
        goto LAB_001027e0;
      }
      *(undefined8 *)(puVar34 + -0x1020) = 0x103e42;
      memcpy((void *)(*(long *)(puVar34 + -0x1000) + 0x75c + (ulong)bVar25 + lVar33),
             (void *)(uVar49 + *(long *)(puVar34 + -0xfd8)),uVar46);
      uVar49 = *(ulong *)(puVar34 + -0xfc0);
      puVar34[*(long *)(puVar34 + -0xfc8) + 0x800] =
           puVar34[*(long *)(puVar34 + -0xfc8) + 0x800] + (char)*(undefined4 *)(puVar34 + -0xfd0);
      break;
    case 1:
      iVar16 = 0;
      uVar46 = 0;
      while( true ) {
        if ((iVar16 == 0x23) || (uVar27 <= uVar49)) goto LAB_00103eb1;
        uVar49 = uVar49 + 1;
        uVar18 = (uint)uVar46 | ((byte)puVar44[uVar49] & 0x7f) << ((byte)iVar16 & 0x1f);
        uVar46 = (ulong)uVar18;
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      iVar16 = 0;
      uVar37 = 0;
      while( true ) {
        if ((iVar16 == 0x23) || (uVar27 <= uVar49)) goto LAB_00103eb1;
        uVar49 = uVar49 + 1;
        uVar37 = uVar37 | ((byte)puVar44[uVar49] & 0x7f) << ((byte)iVar16 & 0x1f);
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      lVar43 = lVar26 * 0x7cc;
      if ((uint)(byte)puVar34[lVar43 + 0x78c] < uVar18 + uVar37) {
LAB_00103eb1:
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x103ecf;
        fwrite("ERR arena fetch\n",1,0x10,__stream);
        goto LAB_001027e0;
      }
      bVar25 = puVar34[lVar43 + 0x800];
      *(long *)(puVar34 + -0xfc8) = lVar43;
      if (0x40 - bVar25 < uVar37) goto LAB_00103ed4;
      *(uint *)(puVar34 + -0xfd0) = uVar37;
      *(undefined8 *)(puVar34 + -0x1020) = 0x104001;
      memcpy((void *)(*(long *)(puVar34 + -0x1000) + 0x75c + (ulong)bVar25 + lVar33),
             (void *)(*(long *)(puVar34 + -0x1000) + 0x6ec + uVar46 + lVar33),(ulong)uVar37);
      puVar34[*(long *)(puVar34 + -0xfc8) + 0x800] =
           puVar34[*(long *)(puVar34 + -0xfc8) + 0x800] + (char)*(undefined4 *)(puVar34 + -0xfd0);
      break;
    case 2:
      uVar49 = uVar46 + 5;
      if (uVar49 <= uVar27) {
        lVar43 = lVar26 * 0x7cc;
        bVar25 = puVar34[lVar43 + 0x802];
        if (bVar25 < 4) {
          bVar36 = puVar34[uVar46 - 0xf57];
          bVar24 = puVar34[uVar46 - 0xf56];
          bVar4 = puVar34[uVar46 - 0xf55];
          bVar5 = puVar34[uVar46 - 0xf54];
          if (((bVar36 < (byte)puVar34[lVar43 + 0xb4]) &&
              (bVar4 < 0x10 && bVar24 < (byte)puVar34[lVar43 + 0x78f])) && (bVar5 < 2)) {
            puVar34[lVar43 + 0x802] = bVar25 + 1;
            *(uint *)(lVar33 + 8 + ((ulong)bVar25 + 0x1e8 + lVar26 * 499) * 4) =
                 CONCAT31(CONCAT21(CONCAT11(bVar5,bVar4),bVar24),bVar36);
            break;
          }
          __stream = *(FILE **)(puVar34 + -0x1008);
          *(undefined8 *)(puVar34 + -0x1020) = 0x1041ae;
          fwrite("ERR bind reject\n",1,0x10,__stream);
          goto LAB_001027e0;
        }
      }
      __stream = *(FILE **)(puVar34 + -0x1008);
      *(undefined8 *)(puVar34 + -0x1020) = 0x1041d1;
      fwrite("ERR bind decode\n",1,0x10,__stream);
      goto LAB_001027e0;
    case 3:
      iVar16 = 0;
      uVar46 = 0;
      while( true ) {
        if ((uVar27 <= uVar49) || (iVar16 == 0x23)) goto LAB_0010416d;
        uVar49 = uVar49 + 1;
        bVar25 = (byte)iVar16 & 0x1f;
        uVar18 = (uint)uVar46 | ((byte)puVar44[uVar49] & 0x7f) << bVar25;
        uVar46 = (ulong)uVar18;
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      iVar16 = 0;
      uVar31 = (ulong)(uint)(0 << bVar25);
      while( true ) {
        if ((iVar16 == 0x23) || (uVar27 <= uVar49)) goto LAB_0010416d;
        uVar49 = uVar49 + 1;
        bVar25 = (byte)iVar16 & 0x1f;
        uVar37 = (uint)uVar31 | ((byte)puVar44[uVar49] & 0x7f) << bVar25;
        uVar31 = (ulong)uVar37;
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      iVar16 = 0;
      uVar29 = 0 << bVar25;
      while( true ) {
        if ((uVar27 <= uVar49) || (iVar16 == 0x23)) goto LAB_0010416d;
        uVar49 = uVar49 + 1;
        uVar29 = uVar29 | ((byte)puVar44[uVar49] & 0x7f) << ((byte)iVar16 & 0x1f);
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      if (uVar18 + uVar29 < 0xd) {
        uVar37 = uVar37 + uVar29;
        uVar28 = (ulong)uVar37;
        lVar43 = lVar26 * 0x7cc + 0x3ff8;
        if (uVar37 <= (byte)puVar34[lVar26 * 0x7cc + 0x800]) {
          lVar45 = *(long *)(puVar34 + -0x1000);
          while (uVar47 = uVar31, uVar47 < uVar28) {
            bVar25 = puVar34[(uVar47 - 0x37f4) + lVar43];
            uVar31 = uVar47 + 1;
            if ((char)bVar25 < '\0') {
              if (bVar25 != 0x80) {
                uVar35 = 0;
                if (uVar31 < uVar28) {
                  uVar35 = puVar34[(uVar47 - 0x37f3) + lVar43];
                  uVar31 = uVar47 + 2;
                }
                uVar47 = (0x101 - bVar25) + uVar46;
                do {
                  if (uVar46 < 0x1c) {
                    *(undefined1 *)(lVar33 + 0x79c + lVar45 + uVar46) = uVar35;
                  }
                  uVar46 = uVar46 + 1;
                } while (uVar46 != uVar47);
              }
            }
            else {
              for (; ((uVar31 - uVar47) - 1 < (ulong)(uint)bVar25 + 1 && (uVar31 < uVar28));
                  uVar31 = uVar31 + 1) {
                if (uVar46 < 0x1c) {
                  *(undefined1 *)(lVar33 + 0x79c + lVar45 + uVar46) =
                       *(undefined1 *)(*(long *)(puVar34 + -0xff8) + 0x75c + uVar31);
                }
                uVar46 = uVar46 + 1;
              }
            }
          }
          break;
        }
      }
      __stream = *(FILE **)(puVar34 + -0x1008);
      *(undefined8 *)(puVar34 + -0x1020) = 0x10406b;
      fwrite("ERR expand reject\n",1,0x12,__stream);
      goto LAB_001027e0;
    case 4:
      if (uVar27 <= uVar49) {
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x1040d5;
        fwrite("ERR signer decode\n",1,0x12,__stream);
        goto LAB_001027e0;
      }
      uVar49 = uVar46 + 2;
      puVar34[lVar26 * 0x7cc + 0x803] = puVar34[uVar46 - 0xf57];
      break;
    default:
      goto switchD_00103b36_default;
    }
    *(int *)(puVar34 + -4000) = *(int *)(puVar34 + -4000) + 1;
  } while (*(int *)(puVar34 + -4000) != *(int *)(puVar34 + -0xff0));
  lVar33 = *(long *)(puVar34 + -0xfe0);
  __stream = *(FILE **)(puVar34 + -0x1008);
  lVar43 = 0;
  puVar32 = (undefined4 *)(*(long *)(puVar34 + -0x1010) + 0x7b8 + lVar33 * 0x7cc);
  do {
    lVar43 = lVar43 + 1;
    *puVar32 = 0;
    puVar32 = puVar32 + 1;
  } while (lVar43 != 4);
  lVar43 = *(long *)(puVar34 + -0xff8);
  bVar25 = puVar34[lVar26 * 0x7cc + 0xb4];
  lVar45 = lVar43;
  for (uVar27 = 0; (uVar27 < bVar25 && (uVar27 != 4)); uVar27 = uVar27 + 1) {
    if (*(byte *)(lVar45 + 0x53e) < (byte)puVar34[lVar26 * 0x7cc + 0xb2]) {
      *(undefined4 *)(lVar45 + 0x7b8) =
           *(undefined4 *)
            (puVar34 + ((ulong)*(byte *)(lVar45 + 0x53e) + 0x144 + lVar26 * 499) * 4 + 0xb6);
    }
    lVar45 = lVar45 + 4;
  }
  lVar45 = lVar26 * 0x7cc;
  for (uVar27 = 0; (uVar27 < (byte)puVar34[lVar45 + 0x802] && (uVar27 != 4)); uVar27 = uVar27 + 1) {
    if (*(byte *)(lVar43 + 0x7a8) < bVar25) {
      bVar36 = *(byte *)(lVar43 + 0x7a9);
      if (((((bVar36 < (byte)puVar34[lVar45 + 0x78f]) && (bVar36 < (byte)puVar34[lVar45 + 0x790]))
           && (puVar34[(ulong)bVar36 + lVar45 + 0x7e4] == '\x01')) &&
          ((bVar24 = *(byte *)(lVar43 + 0x7aa), 0x17 < bVar24 &&
           (((*(byte *)(lVar43 + 0x7ab) & 1) == 0 ||
            (((byte)puVar34[lVar45 + 0x803] >> (bVar36 & 0x1f) & 1) != 0)))))) &&
         (((ulong)bVar24 + 4 <= (ulong)(byte)puVar34[lVar26 * 0x7cc + 0x744] &&
          (((uVar18 = *(uint *)(puVar34 + *(long *)(puVar34 + -0x1000) + (ulong)bVar24 + 0x748),
            (char)uVar18 == '\x02' && ((char)(uVar18 >> 8) == '\x01')) &&
           (((char)(uVar18 >> 0x10) == '\x01' && ((uVar18 & 0x1000000) != 0)))))))) {
        *(uint *)(puVar34 + (lVar33 * 499 + 0x1ee + (ulong)*(byte *)(lVar43 + 0x7a8)) * 4 + 0xa8) =
             uVar18;
      }
    }
    lVar43 = lVar43 + 4;
  }
  lVar33 = *(long *)(puVar34 + -0x1010);
  lVar43 = *(long *)(puVar34 + -0x1000);
  puVar34[lVar26 * 0x7cc + 0x801] = 1;
  uVar18 = ((byte)puVar34[lVar26 * 0x7cc + 0x800] ^ 0xc048c996) * 0x1000193 ^ 0x811c9dc5;
  for (uVar27 = 0; uVar27 < (byte)puVar34[lVar26 * 0x7cc + 0x800]; uVar27 = uVar27 + 1) {
    uVar18 = (uVar18 ^ *(byte *)(lVar33 + 0x75c + lVar43 + uVar27)) * 0x1000193;
  }
  lVar33 = 0;
  uVar18 = (((byte)puVar34[lVar45 + 0x802] ^ uVar18 ^ 0x811c9dc5) * 0x1000193 ^
            (uint)(byte)puVar34[lVar26 * 0x7cc + 0x803] ^ 0x811c9dc5) * 0x1000193 ^ 0x811c9dc5;
  do {
    pbVar1 = (byte *)(*(long *)(puVar34 + -0x1010) + 0x7a8 + *(long *)(puVar34 + -0x1000) + lVar33);
    lVar33 = lVar33 + 1;
    uVar18 = (uVar18 ^ *pbVar1) * 0x1000193;
  } while (lVar33 != 0x10);
  uVar18 = uVar18 ^ 0x811c9dc5;
  for (uVar27 = 0; uVar27 < (ulong)bVar25 << 2; uVar27 = uVar27 + 1) {
    uVar18 = (uVar18 ^ *(byte *)(*(long *)(puVar34 + -0x1010) + 0x7b8 + *(long *)(puVar34 + -0x1000)
                                + uVar27)) * 0x1000193;
  }
  uVar37 = *(uint *)(puVar34 + -0xfe8);
  *(uint *)(puVar34 + lVar26 * 0x7cc + 0x870) = uVar18;
  *(undefined8 *)(puVar34 + -0x1020) = 0x1043ea;
  fprintf(__stream,"OK attested slot %u attest_root=0x%08x signers=0x%02x\n",(ulong)uVar37);
  goto LAB_001027e0;
LAB_0010416d:
  __stream = *(FILE **)(puVar34 + -0x1008);
  *(undefined8 *)(puVar34 + -0x1020) = 0x10418b;
  fwrite("ERR expand decode\n",1,0x12,__stream);
  goto LAB_001027e0;
LAB_00104e9c:
  do {
    iVar16 = 0;
    uVar31 = 0;
    while( true ) {
      if ((iVar16 == 0x23) || (uVar46 <= uVar49)) {
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x105312;
        fwrite("ERR receipt decode\n",1,0x13,__stream);
        goto LAB_001027e0;
      }
      uVar49 = uVar49 + 1;
      bVar25 = (byte)iVar16 & 0x1f;
      uVar18 = (uint)uVar31 | ((byte)puVar44[uVar49] & 0x7f) << bVar25;
      uVar31 = (ulong)uVar18;
      if (-1 < (char)puVar44[uVar49]) break;
      iVar16 = iVar16 + 7;
    }
    if (uVar18 == 0) {
      iVar16 = 0;
      while( true ) {
        if ((iVar16 == 0x23) || (uVar46 <= uVar49)) goto LAB_001056b1;
        uVar49 = uVar49 + 1;
        uVar18 = (uint)uVar31 | ((byte)puVar44[uVar49] & 0x7f) << ((byte)iVar16 & 0x1f);
        uVar31 = (ulong)uVar18;
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      if (uVar46 < uVar31 + uVar49) {
LAB_001056b1:
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x1056cf;
        fwrite("ERR quote add\n",1,0xe,__stream);
        goto LAB_001027e0;
      }
      *(ulong *)(puVar34 + -0xfc0) = uVar31 + uVar49;
      *(uint *)(puVar34 + -0xfc8) = uVar18;
      bVar25 = puVar34[*(long *)(puVar34 + -0xff0) + 0x78c];
      if (0x40 - bVar25 < uVar18) {
LAB_001057d6:
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x1057f4;
        fwrite("ERR quote reject\n",1,0x11,__stream);
        goto LAB_001027e0;
      }
      *(undefined8 *)(puVar34 + -0x1020) = 0x105695;
      memcpy((void *)(*(long *)(puVar34 + -0x1000) + (ulong)bVar25),pbVar1 + uVar49,uVar31);
      uVar49 = *(ulong *)(puVar34 + -0xfc0);
      puVar34[*(long *)(puVar34 + -0xff0) + 0x78c] =
           puVar34[*(long *)(puVar34 + -0xff0) + 0x78c] + (char)*(undefined4 *)(puVar34 + -0xfc8);
    }
    else if (uVar18 == 1) {
      iVar16 = 0;
      uVar31 = (ulong)(uint)(0 << bVar25);
      while( true ) {
        if ((uVar46 <= uVar49) || (iVar16 == 0x23)) goto LAB_00105866;
        uVar49 = uVar49 + 1;
        uVar18 = (uint)uVar31 | ((byte)puVar44[uVar49] & 0x7f) << ((byte)iVar16 & 0x1f);
        uVar31 = (ulong)uVar18;
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      iVar16 = 0;
      uVar37 = 0;
      while( true ) {
        if ((iVar16 == 0x23) || (uVar46 <= uVar49)) goto LAB_00105866;
        uVar49 = uVar49 + 1;
        uVar37 = uVar37 | ((byte)puVar44[uVar49] & 0x7f) << ((byte)iVar16 & 0x1f);
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      lVar26 = uVar27 * 0x7cc;
      if ((uint)(byte)puVar34[lVar26 + 0x744] < uVar18 + uVar37) {
LAB_00105866:
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x105884;
        fwrite("ERR quote fetch\n",1,0x10,__stream);
        goto LAB_001027e0;
      }
      bVar25 = puVar34[lVar26 + 0x78c];
      *(long *)(puVar34 + -0xfc0) = lVar26;
      if (0x40 - bVar25 < uVar37) goto LAB_001057d6;
      *(uint *)(puVar34 + -0xfc8) = uVar37;
      *(undefined8 *)(puVar34 + -0x1020) = 0x1058ea;
      memcpy((void *)((ulong)bVar25 + *(long *)(puVar34 + -0x1000)),
             (void *)(*(long *)(puVar34 + -0xfe0) + 0x6a0 + uVar31 + *(long *)(puVar34 + -0x1010)),
             (ulong)uVar37);
      puVar34[*(long *)(puVar34 + -0xfc0) + 0x78c] =
           puVar34[*(long *)(puVar34 + -0xfc0) + 0x78c] + (char)*(undefined4 *)(puVar34 + -0xfc8);
    }
    else if (uVar18 == 2) {
      iVar16 = 0;
      uVar18 = 0;
      uVar31 = uVar49;
      while( true ) {
        if ((uVar46 <= uVar31) || (iVar16 == 0x23)) goto LAB_00105550;
        uVar18 = uVar18 | ((byte)puVar44[uVar31 + 1] & 0x7f) << ((byte)iVar16 & 0x1f);
        if (-1 < (char)puVar44[uVar31 + 1]) break;
        iVar16 = iVar16 + 7;
        uVar31 = uVar31 + 1;
      }
      if ((3 < uVar18) || (uVar49 = uVar31 + 5, uVar46 < uVar49)) {
LAB_00105550:
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x10556e;
        fwrite("ERR window decode\n",1,0x12,__stream);
        goto LAB_001027e0;
      }
      if ((2 < (byte)puVar34[uVar31 - 0xf56] || 1 < (byte)puVar34[uVar31 - 0xf57]) ||
         (7 < (byte)(puVar34[uVar31 - 0xf55] - 1))) {
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x105835;
        fwrite("ERR window reject\n",1,0x12,__stream);
        goto LAB_001027e0;
      }
      *(uint *)(*(long *)(puVar34 + -0x1010) + 0xc + ((ulong)uVar18 + 0x1c8 + uVar27 * 499) * 4) =
           CONCAT31(CONCAT21(CONCAT11(puVar34[uVar31 - 0xf54],puVar34[uVar31 - 0xf55]),
                             puVar34[uVar31 - 0xf56]),puVar34[uVar31 - 0xf57]);
      if ((uint)(byte)puVar34[uVar27 * 0x7cc + 0x78e] < uVar18 + 1) {
        puVar34[uVar27 * 0x7cc + 0x78e] = (char)uVar18 + '\x01';
      }
    }
    else {
      if (uVar18 != 3) goto switchD_00103b36_default;
      iVar16 = 0;
      uVar18 = 0 << bVar25;
      while( true ) {
        if ((iVar16 == 0x23) || (uVar46 <= uVar49)) goto LAB_00105341;
        uVar49 = uVar49 + 1;
        uVar18 = uVar18 | ((byte)puVar44[uVar49] & 0x7f) << ((byte)iVar16 & 0x1f);
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      iVar16 = 0;
      uVar31 = 0;
      while( true ) {
        if ((uVar46 <= uVar49) || (iVar16 == 0x23)) goto LAB_00105341;
        uVar49 = uVar49 + 1;
        bVar25 = (byte)iVar16 & 0x1f;
        uVar37 = (uint)uVar31 | ((byte)puVar44[uVar49] & 0x7f) << bVar25;
        uVar31 = (ulong)uVar37;
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      iVar16 = 0;
      uVar28 = (ulong)(uint)(0 << bVar25);
      while( true ) {
        if ((uVar46 <= uVar49) || (iVar16 == 0x23)) goto LAB_00105341;
        uVar49 = uVar49 + 1;
        uVar29 = (uint)uVar28 | ((byte)puVar44[uVar49] & 0x7f) << ((byte)iVar16 & 0x1f);
        uVar28 = (ulong)uVar29;
        if (-1 < (char)puVar44[uVar49]) break;
        iVar16 = iVar16 + 7;
      }
      if ((0x10 < uVar18 + uVar29) ||
         ((uint)(byte)puVar34[*(long *)(puVar34 + -0xff0) + 0x78c] < uVar37 + uVar29)) {
LAB_00105341:
        __stream = *(FILE **)(puVar34 + -0x1008);
        *(undefined8 *)(puVar34 + -0x1020) = 0x10535f;
        fwrite("ERR patch reject\n",1,0x11,__stream);
        goto LAB_001027e0;
      }
      *(undefined8 *)(puVar34 + -0x1020) = 0x1055b6;
      memcpy((void *)((ulong)uVar18 + *(long *)(puVar34 + -0xfd8) + *(long *)(puVar34 + -0x1010)),
             (void *)(uVar31 + *(long *)(puVar34 + -0x1000)),uVar28);
    }
    *(int *)(puVar34 + -0xff8) = *(int *)(puVar34 + -0xff8) + 1;
  } while (*(int *)(puVar34 + -0xff8) != *(int *)(puVar34 + -4000));
  lVar26 = *(long *)(puVar34 + -0xfe0);
  bVar14 = false;
  lVar43 = uVar27 * 0x7cc;
  __stream = *(FILE **)(puVar34 + -0x1008);
  lVar33 = *(long *)(puVar34 + -0xfd0);
  puVar40 = (undefined8 *)(*(long *)(puVar34 + -0x1010) + 0x73c + lVar26);
  *(undefined2 *)(*(long *)(puVar34 + -0x1010) + 0x6e7 + lVar43) = 0;
  *puVar40 = 0;
  while( true ) {
    lVar48 = 0;
    lVar45 = lVar33;
    do {
      bVar25 = *(byte *)(lVar45 + 0x72e);
      bVar36 = puVar34[lVar43 + 0x78f];
      if ((bVar25 != 0) && (cVar6 = *(char *)(lVar45 + 0x72c), (bool)cVar6 == bVar14)) {
        if (8 < (uint)bVar25 + (uint)bVar36) goto LAB_001057f9;
        uVar35 = *(undefined1 *)(lVar45 + 0x72d);
        bVar25 = bVar25 + bVar36;
        do {
          uVar46 = (ulong)bVar36;
          bVar36 = bVar36 + 1;
          puVar34[uVar46 + lVar43 + 0x7e4] = uVar35;
        } while (bVar25 != bVar36);
        puVar34[lVar43 + 0x78f] = bVar25;
        if (cVar6 == '\0') {
          puVar34[lVar43 + 0x790] = bVar25;
        }
      }
      lVar48 = lVar48 + 1;
      lVar45 = lVar45 + 4;
    } while (lVar48 != 4);
    if (bVar14) break;
    bVar14 = true;
  }
  if (puVar34[uVar27 * 0x7cc + 0x78f] == 0) {
LAB_001057f9:
    *(undefined8 *)(puVar34 + -0x1020) = 0x105812;
    fwrite("ERR loaded accounts\n",1,0x14,__stream);
  }
  else {
    uVar18 = ((byte)puVar34[uVar27 * 0x7cc + 0x78c] ^ 0xd04ed291) * 0x1000193 ^ 0x811c9dc5;
    for (uVar46 = 0; uVar46 < (byte)puVar34[uVar27 * 0x7cc + 0x78c]; uVar46 = uVar46 + 1) {
      uVar18 = (uVar18 ^ *(byte *)(*(long *)(puVar34 + -0x1000) + uVar46)) * 0x1000193;
    }
    uVar18 = uVar18 ^ 0x811c9dc5;
    lVar43 = 0;
    do {
      pbVar1 = (byte *)(*(long *)(puVar34 + -0x1010) + 0x72c + lVar26 + lVar43);
      lVar43 = lVar43 + 1;
      uVar18 = (uVar18 ^ *pbVar1) * 0x1000193;
    } while (lVar43 != 0x10);
    uVar18 = uVar18 ^ 0x811c9dc5;
    uVar46 = 0;
    do {
      pbVar1 = (byte *)((long)puVar40 + uVar46);
      uVar46 = uVar46 + 1;
      uVar18 = (uVar18 ^ *pbVar1) * 0x1000193;
    } while (uVar46 < (byte)puVar34[uVar27 * 0x7cc + 0x78f]);
    lVar26 = uVar27 * 0x7cc;
    puVar34[lVar26 + 0x78d] = 1;
    *(uint *)(puVar34 + lVar26 + 0x7fc) =
         (uVar18 ^ (byte)puVar34[lVar26 + 0x790] ^ 0x811c9dc5) * 0x1000193;
    *(undefined8 *)(puVar34 + -0x1020) = 0x1057a3;
    FUN_001017b0(lVar33);
    uVar18 = *(uint *)(puVar34 + lVar26 + 0x7fc);
    *(undefined8 *)(puVar34 + -0x1020) = 0x1057d1;
    fprintf(__stream,"OK quoted slot %u quote_root=0x%08x loaded=%u writable=%u\n",
            (ulong)*(uint *)(puVar34 + -0xfe8),(ulong)uVar18);
  }
  goto LAB_001027e0;
switchD_00103b36_default:
  __stream = *(FILE **)(puVar34 + -0x1008);
  *(undefined8 *)(puVar34 + -0x1020) = 0x1040b2;
  fwrite("ERR bad opcode\n",1,0xf,__stream);
  goto LAB_001027e0;
}



// Function _DT_FINI @ 00105950

void _DT_FINI(void)

{
  return;
}



// Function __libc_start_main @ 00109000

/* WARNING: Control flow encountered bad instruction data */

void __libc_start_main(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function __errno_location @ 00109008

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int * __errno_location(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function strncmp @ 00109010

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int strncmp(char *__s1,char *__s2,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function _ITM_deregisterTMCloneTable @ 00109018

/* WARNING: Control flow encountered bad instruction data */

void _ITM_deregisterTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function _exit @ 00109020

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _exit(int __status)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function fread @ 00109028

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t fread(void *__ptr,size_t __size,size_t __n,FILE *__stream)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function setsockopt @ 00109030

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int setsockopt(int __fd,int __level,int __optname,void *__optval,socklen_t __optlen)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function getpid @ 00109038

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__pid_t getpid(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function fclose @ 00109040

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int fclose(FILE *__stream)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function strlen @ 00109048

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t strlen(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function memset @ 00109050

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memset(void *__s,int __c,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function strnlen @ 00109058

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t strnlen(char *__string,size_t __maxlen)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function close @ 00109060

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int close(int __fd)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function srand @ 00109068

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void srand(uint __seed)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function fgets @ 00109070

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * fgets(char *__s,int __n,FILE *__stream)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function strcmp @ 00109078

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int strcmp(char *__s1,char *__s2)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function signal @ 00109080

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function fprintf @ 00109088

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int fprintf(FILE *__stream,char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function __gmon_start__ @ 00109090

/* WARNING: Control flow encountered bad instruction data */

void __gmon_start__(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function strtol @ 00109098

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long strtol(char *__nptr,char **__endptr,int __base)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function memcpy @ 001090a0

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memcpy(void *__dest,void *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function time @ 001090a8

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

time_t time(time_t *__timer)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function listen @ 001090b0

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int listen(int __fd,int __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function fdopen @ 001090b8

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

FILE * fdopen(int __fd,char *__modes)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function setvbuf @ 001090c0

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int setvbuf(FILE *__stream,char *__buf,int __modes,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function bind @ 001090c8

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int bind(int __fd,sockaddr *__addr,socklen_t __len)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function waitpid @ 001090d0

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__pid_t waitpid(__pid_t __pid,int *__stat_loc,int __options)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function fopen @ 001090d8

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

FILE * fopen(char *__filename,char *__modes)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function perror @ 001090e0

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void perror(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function strtok @ 001090e8

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strtok(char *__s,char *__delim)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function accept @ 001090f0

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int accept(int __fd,sockaddr *__addr,socklen_t *__addr_len)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function exit @ 001090f8

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void exit(int __status)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function fwrite @ 00109100

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function _ITM_registerTMCloneTable @ 00109108

/* WARNING: Control flow encountered bad instruction data */

void _ITM_registerTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function getrandom @ 00109110

/* WARNING: Control flow encountered bad instruction data */

void getrandom(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function fork @ 00109118

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__pid_t fork(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function rand @ 00109120

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int rand(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function socket @ 00109128

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int socket(int __domain,int __type,int __protocol)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// Function __cxa_finalize @ 00109130

/* WARNING: Control flow encountered bad instruction data */

void __cxa_finalize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}
