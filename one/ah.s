.cpu cortex-m3
.thumb

// SRAM 20 KB.. 0x2000 (alamat SRAM) + 0x5000 (20 KB)
.word 0x20005000
.word _reset
.thumb_func
_reset:
	bl main
	b .
