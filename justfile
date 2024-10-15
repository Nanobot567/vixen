# idk, i like just :3

default:
  rm -rf src/sys.h.gch

  nasm -felf32 src/asm/boot.asm -o boot.o
  nasm -felf32 src/asm/gdt.asm -o gdt.o

  i686-elf-gcc -c src/libc/stdio/* -ffreestanding -O2 -Wall -Wextra -I src/libc/include
  i686-elf-gcc -c src/libc/string/* -ffreestanding -O2 -Wall -Wextra -I src/libc/include

  i686-elf-gcc -c src/misc/* -ffreestanding -O2 -Wall -Wextra -I src/misc/include/
  
  i686-elf-gcc -c src/kernel/* -ffreestanding -O2 -Wall -Wextra -I src/kernel/include

  i686-elf-gcc -c src/* -ffreestanding -O2 -Wall -Wextra

  i686-elf-gcc -T linker.ld -o vixenOS.bin -ffreestanding -O2 -nostdlib *.o -lgcc

  mkdir -p isodir/boot/grub
  cp vixenOS.bin isodir/boot/vixen.bin
  cp grub.cfg isodir/boot/grub/grub.cfg
  grub2-mkrescue -o vixenOS.iso isodir

  rm -rf *.o
  rm -rf isodir

  qemu-system-i386 -cdrom vixenOS.iso -audiodev pa,id=snd0 -machine pcspk-audiodev=snd0 -rtc base=localtime

clean:
  rm -rf *.o
