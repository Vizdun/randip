#include <stdio.h>
#include <openssl/rand.h>

int main()
{
  int valid_ip = 0;
  unsigned char buf[4];

  while (valid_ip == 0)
  {
    RAND_bytes(buf, 4);

    unsigned int i = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | (buf[3]);

    if (
        (i >= 0x01000000 && i <= 0x09FFFFFF) || // 1.0.0.0 - 9.255.255.255
        (i >= 0x0B000000 && i <= 0x7EFFFFFF) || // 11.0.0.0 - 126.255.255.255
        (i >= 0x81000000 && i <= 0xA9FDFFFF) || // 129.0.0.0 - 169.253.255.255
        (i >= 0xA9FF0000 && i <= 0xAC0FFFFF) || // 169.255.0.0 - 172.15.255.255
        (i >= 0xAC200000 && i <= 0xBF0001FF) || // 172.32.0.0 - 191.0.1.255
        (i >= 0xC0000300 && i <= 0xC05862FF) || // 192.0.3.0 - 192.88.98.255
        (i >= 0xC0586400 && i <= 0xC0A7FFFF) || // 192.88.100.0 - 192.167.255.255
        (i >= 0xC0A90000 && i <= 0xC611FFFF) || // 192.169.0.0 - 198.17.255.255
        (i >= 0xC6140000 && i <= 0xDFFFFFFF) // 198.20.0.0 - 223.255.255.255
    )
    {
      valid_ip = 1;
    }
  }

  printf("%d.%d.%d.%d", buf[0], buf[1], buf[2], buf[3]);
}