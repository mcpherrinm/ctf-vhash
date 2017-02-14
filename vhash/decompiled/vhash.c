void __fastcall vhash_init(vhash_ctx *vctx)
{
  memcpy(vctx, "vhas", 4uLL);
  memcpy(&vctx->state[1], "h: r", 4uLL);
  memcpy(&vctx->state[2], "ock ", 4uLL);
  memcpy(&vctx->state[3], "hard", 4uLL);
  memcpy(&vctx->state[4], " 102", 4uLL);
  memcpy(&vctx->state[5], "4 bi", 4uLL);
  memcpy(&vctx->state[6], "t se", 4uLL);
  memcpy(&vctx->state[7], "curi", 4uLL);
  memcpy(&vctx->state[8], "ty. ", 4uLL);
  memcpy(&vctx->state[9], "For ", 4uLL);
  memcpy(&vctx->state[10], "thos", 4uLL);
  memcpy(&vctx->state[11], "e sp", 4uLL);
  memcpy(&vctx->state[12], "ecia", 4uLL);
  memcpy(&vctx->state[13], "l mo", 4uLL);
  memcpy(&vctx->state[14], "mome", 4uLL);
  memcpy(&vctx->state[15], "nts ", 4uLL);
  memcpy(&vctx->state[16], "when", 4uLL);
  memcpy(&vctx->state[17], " you", 4uLL);
  memcpy(&vctx->state[18], " nee", 4uLL);
  memcpy(&vctx->state[19], "d th", 4uLL);
  memcpy(&vctx->state[20], "robb", 4uLL);
  memcpy(&vctx->state[21], "ing ", 4uLL);
  memcpy(&vctx->state[22], "perf", 4uLL);
  memcpy(&vctx->state[23], "orma", 4uLL);
  memcpy(&vctx->state[24], "nce.", 4uLL);
  memcpy(&vctx->state[25], " Ask", 4uLL);
  memcpy(&vctx->state[26], " you", 4uLL);
  memcpy(&vctx->state[27], "r do", 4uLL);
  memcpy(&vctx->state[28], "ctor", 4uLL);
  memcpy(&vctx->state[29], " abo", 4uLL);
  memcpy(&vctx->state[30], "ut v", 4uLL);
  memcpy(&vctx->state[31], "hash", 4uLL);
}

void __fastcall vhash_round(vhash_ctx *vctx)
{
  uint32_t v1; // edx@5
  int i; // [sp+10h] [bp-8h]@1
  int ia; // [sp+10h] [bp-8h]@4
  int ib; // [sp+10h] [bp-8h]@7
  int ic; // [sp+10h] [bp-8h]@10
  int id; // [sp+10h] [bp-8h]@13
  uint32_t t; // [sp+14h] [bp-4h]@13

  for ( i = 0; i <= 31; ++i )
    ++vctx->state[i];
  for ( ia = 0; ia <= 31; ++ia )
  {
    v1 = __ROL4__(vctx->state[ia], ia);
    vctx->state[ia] = v1;
  }
  for ( ib = 0; ib <= 31; ++ib )
    vctx->state[ib] += vctx->state[((((unsigned int)((ib + 1) >> 31) >> 27) + (_BYTE)ib + 1) & 0x1F)
                                 - ((unsigned int)((ib + 1) >> 31) >> 27)];
  for ( ic = 0; ic <= 31; ++ic )
    vctx->state[ic] ^= vctx->state[((((unsigned int)((ic + 7) >> 31) >> 27) + (_BYTE)ic + 7) & 0x1F)
                                 - ((unsigned int)((ic + 7) >> 31) >> 27)];
  t = vctx->state[0];
  for ( id = 0; id <= 30; ++id )
    vctx->state[id] = vctx->state[id + 1];
  vctx->state[31] = t;
}

void __fastcall vhash_update(vhash_ctx *vctx, uint32_t (*in)[4])
{
  int i; // [sp+1Ch] [bp-4h]@1
  int ia; // [sp+1Ch] [bp-4h]@4
  int ib; // [sp+1Ch] [bp-4h]@7
  int ic; // [sp+1Ch] [bp-4h]@10

  for ( i = 0; i <= 31; ++i )
    vctx->state[i] += (*in)[((((unsigned int)((unsigned __int64)i >> 32) >> 30) + (_BYTE)i) & 3)
                          - ((unsigned int)((unsigned __int64)i >> 32) >> 30)];
  for ( ia = 0; ia <= 511; ++ia )
    vhash_round(vctx);
  for ( ib = 0; ib <= 31; ++ib )
    vctx->state[ib] ^= (*in)[((((unsigned int)((unsigned __int64)ib >> 32) >> 30) + (_BYTE)ib) & 3)
                           - ((unsigned int)((unsigned __int64)ib >> 32) >> 30)];
  for ( ic = 0; ic <= 511; ++ic )
    vhash_round(vctx);
}

void __fastcall vhash_final(vhash_ctx *vctx, uint32_t len)
{
  __int64 v2; // rax@1
  uint32_t f[4]; // [sp+10h] [bp-20h]@1
  __int64 v4; // [sp+28h] [bp-8h]@1

  v4 = *MK_FP(__FS__, 40LL);
  f[0] = 0x80000000;
  f[1] = len;
  f[2] = 0;
  f[3] = 0xFFFFFFFF;
  vhash_update(vctx, (uint32_t (*)[4])f);
  v2 = *MK_FP(__FS__, 40LL) ^ v4;
}

void __fastcall print_block(uint32_t (*block)[4])
{
  fprintf(stderr, "Block: %08x %08x %08x %08x\n", (*block)[0], (*block)[1], (*block)[2], (*block)[3]);
}

void __fastcall print_state(vhash_ctx *vctx)
{
  int i; // [sp+1Ch] [bp-4h]@1

  fwrite("State:\n", 1uLL, 7uLL, stderr);
  for ( i = 0; i <= 7; ++i )
    fprintf(
      stderr,
      "%08x %08x %08x %08x\n",
      vctx->state[4 * i],
      vctx->state[4 * i + 1],
      vctx->state[4 * i + 2],
      vctx->state[4 * i + 3]);
}

void __fastcall print_hash(vhash_ctx *vctx)
{
  int i; // [sp+1Ch] [bp-4h]@1

  for ( i = 0; i <= 7; ++i )
    printf(
      "%08x%08x%08x%08x",
      vctx->state[4 * i],
      vctx->state[4 * i + 1],
      vctx->state[4 * i + 2],
      vctx->state[4 * i + 3]);
}
