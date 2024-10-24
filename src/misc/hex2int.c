int hex2int(char *hdec) {
  int finalval = 0;
  while (*hdec) {
    int onebyte = *hdec++;

    if (onebyte >= '0' && onebyte <= '9') {
      onebyte = onebyte - '0';
    } else if (onebyte >= 'a' && onebyte <= 'f') {
      onebyte = onebyte - 'a' + 10;
    } else if (onebyte >= 'A' && onebyte <= 'F') {
      onebyte = onebyte - 'A' + 10;
    }

    finalval = (finalval << 4) | (onebyte & 0xF);
  }
  return finalval;
}
