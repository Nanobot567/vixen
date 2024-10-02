# idk, i like just :3

default:
  rm -rf src/sys.h.gch

  nasm -felf32 src/boot/boot.asm -o boot.o

  i686-elf-gcc -c src/* -ffreestanding -O2 -Wall -Wextra
  i686-elf-gcc -T linker.ld -o vixenOS.bin -ffreestanding -O2 -nostdlib *.o -lgcc

  mkdir -p isodir/boot/grub
  cp vixenOS.bin isodir/boot/vixen.bin
  cp grub.cfg isodir/boot/grub/grub.cfg
  grub2-mkrescue -o vixenOS.iso isodir

  rm -rf *.o
  rm -rf isodir

  qemu-system-i386 -cdrom vixenOS.iso -audiodev pa,id=snd0 -machine pcspk-audiodev=snd0
