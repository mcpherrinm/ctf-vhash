int __cdecl main(int argc, const char **argv, const char **envp)
{
  int result; // eax@11
  __int64 v4; // rcx@11
  uint8_t inbyte; // [sp+Bh] [bp-B5h]@3
  int i; // [sp+Ch] [bp-B4h]@2
  uint32_t size; // [sp+10h] [bp-B0h]@1
  int done; // [sp+14h] [bp-ACh]@1
  ssize_t ret; // [sp+18h] [bp-A8h]@3
  uint32_t block[4]; // [sp+20h] [bp-A0h]@2
  vhash_ctx vctx; // [sp+30h] [bp-90h]@1
  __int64 v12; // [sp+B8h] [bp-8h]@1

  v12 = *MK_FP(__FS__, 40LL);
  done = 0;
  vhash_init(&vctx);
  size = 0;
  while ( !done )
  {
    memset(block, 0, 0x10uLL);
    for ( i = 0; (unsigned int)i <= 15; ++i )
    {
      ret = read(0, &inbyte, 1uLL);
      if ( ret == 1 )
      {
        ++size;
        block[i / 4] |= inbyte << 8 * (3 - (char)i % 4);
      }
      else if ( ret <= 0 )
      {
        done = 1;
        break;
      }
    }
    vhash_update(&vctx, (uint32_t (*)[4])block);
  }
  vhash_final(&vctx, size);
  print_hash(&vctx);
  puts(" -");
  result = 0;
  v4 = *MK_FP(__FS__, 40LL) ^ v12;
  return result;
}
