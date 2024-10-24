# idk, i like just :3

default:
  rm -rf src/sys.h.gch

  nasm -felf32 src/asm/boot.asm -o boot.ao # .ao to have precedence over other .os
  nasm -felf32 src/asm/gdt.asm -o gdt.ao
  nasm -felf32 src/asm/isr.asm -o isr.ao
  nasm -felf32 src/asm/irq.asm -o irq.ao

  i686-elf-gcc -c src/libc/stdio/* -ffreestanding -O2 -Wall -Wextra -I src/libc/include
  i686-elf-gcc -c src/libc/string/* -ffreestanding -O2 -Wall -Wextra -I src/libc/include

  i686-elf-gcc -c src/misc/* -ffreestanding -O2 -Wall -Wextra -I src/misc/include/

  i686-elf-gcc -c src/shell/* -ffreestanding -O2 -Wall -Wextra -I src/shell/include/
  
  i686-elf-gcc -c src/kernel/* -ffreestanding -O2 -Wall -Wextra -I src/kernel/include

  i686-elf-gcc -c src/* -ffreestanding -O2 -Wall -Wextra -g

  i686-elf-gcc -T linker.ld -o vixenOS.bin -ffreestanding -fno-leading-underscore -O2 -nostdlib *.ao *.o -lgcc -g

  objcopy --only-keep-debug vixenOS.bin vixenOS.sym

  mkdir -p isodir/boot/grub
  cp vixenOS.bin isodir/boot/vixen.bin
  cp grub.cfg isodir/boot/grub/grub.cfg
  grub2-mkrescue -o vixenOS.iso isodir

  just clean

  rm -rf isodir

  qemu-system-i386 -cdrom vixenOS.iso -audiodev pa,id=snd0 -machine pcspk-audiodev=snd0 -rtc base=localtime

clean:
  rm -rf *.ao
  rm -rf *.o
