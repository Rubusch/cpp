# TODO

## example for converting a string having a hexadecimal number / stream to an array of integers
  pSrc = data.c_str();
  pDst = mData + DATA_AUDIO_SONG_STARTPOS; // set byte 0, 1, 2, 3                                                                                                             
  size = DATA_AUDIO_SONG_OFFSET;

// TODO simplify using str util functions                                                                                                                                     
  char ch[3]; ch[2] = '\0';
  for (auto idx=0; idx < 2*size; idx += 2)
    {
      ch[0] = pSrc[idx];
      ch[1] = pSrc[idx+1];
      pDst[idx/2] = std::strtol(ch, NULL, 16);
    }

  pDst[0] |= DATA_FIELD_ENABLED;

