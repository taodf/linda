# Linda Operating System项目所有

# 为了暂时的开发方便，这里舍弃了所有的可配置内容，
# 统一使用默认设置，后续将会添加针对不同平台的配置。

.PHONY: kernel image debug clean

ROOT := $(PWD)
ARCH ?= x86
PREFIX ?= i686-elf

.EXPORT_ALL_VARIABLES:

MAKE_RULES := $(ROOT)/Rules.make
$(info Makefile规则文件: $(MAKE_RULES))
LINK_RULES := $(ROOT)/kernel.ld
$(info 内核链接文件: $(LINK_RULES))

# gnu编译工具链
AS := $(PREFIX)-as
CC := $(PREFIX)-gcc
LD := $(PREFIX)-ld
OBJCOPY := $(PREFIX)-objcopy
OBJDUMP := $(PREFIX)-objdump
NM := $(PREFIX)-nm

INCLUDE_FLAGS := -I $(ROOT)/include/kernel	\
				-I $(ROOT)/include/arch/$(ARCH)
ASM_FLAGS := -g
C_FLAGS := -ffreestanding -std=gnu99 -g -Wall -Wextra
LD_FLAGS := -T $(LINK_RULES) -g

ARCHIVES := arch/$(ARCH)/arch.o init/init.o mm/mm.o kernel/kernel.o
LIBS := lib/lib.o
DRIVERS := drivers/drivers.o fs/fs.o
USRS := usr/bin/processA.bin usr/bin/processB.bin
SUB_DIRS := arch init mm lib drivers fs kernel usr

lindasubdirs:
	@echo "linda subset directories is handing...";
	@set -e; \
	for dir in $(SUB_DIRS); \
	  do $(MAKE) -C $$dir; \
	done;

kernel: lindasubdirs
	@echo "kernel is building...";
	$(LD) $(LD_FLAGS) -o linda.bin $(ARCHIVES) $(LIBS) $(DRIVERS) $(USRS)

ISODIR := isodir/boot/grub
image: kernel
	@echo "kernel image is creating...";
	rm -rf isodir;
	mkdir -p $(ISODIR);
	cp grub.cfg $(ISODIR);
	cp linda.bin $(ISODIR)/../;
	grub-mkrescue -o linda.iso $(ISODIR)/../../;

debug: image
	@echo "debug kernel using bochs...";
	$(OBJCOPY) --only-keep-debug linda.bin linda.elf;
	nm linda.elf | awk '{ print $$1" "$$3 }' > linda.sym;
	bochs -f bochs.cfg;

clean:
	@echo "directories is cleanning...";
	rm -rf isodir;
	@echo "files is cleanning...";
	rm -rf *.o; rm -rf *.bin; rm -rf *.iso; \
	set -e; \
	for dir in $(SUB_DIRS); \
	  do $(MAKE) -C $$dir clean; \
	done; \
