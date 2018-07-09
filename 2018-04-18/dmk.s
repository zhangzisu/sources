
dmk:     file format elf64-x86-64


Disassembly of section .init:

0000000000400428 <_init>:
  400428:	48 83 ec 08          	sub    $0x8,%rsp
  40042c:	48 8b 05 c5 0b 20 00 	mov    0x200bc5(%rip),%rax        # 600ff8 <__gmon_start__>
  400433:	48 85 c0             	test   %rax,%rax
  400436:	74 02                	je     40043a <_init+0x12>
  400438:	ff d0                	callq  *%rax
  40043a:	48 83 c4 08          	add    $0x8,%rsp
  40043e:	c3                   	retq   

Disassembly of section .plt:

0000000000400440 <.plt>:
  400440:	ff 35 c2 0b 20 00    	pushq  0x200bc2(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400446:	ff 25 c4 0b 20 00    	jmpq   *0x200bc4(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40044c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400450 <printf@plt>:
  400450:	ff 25 c2 0b 20 00    	jmpq   *0x200bc2(%rip)        # 601018 <printf@GLIBC_2.2.5>
  400456:	68 00 00 00 00       	pushq  $0x0
  40045b:	e9 e0 ff ff ff       	jmpq   400440 <.plt>

0000000000400460 <rand@plt>:
  400460:	ff 25 ba 0b 20 00    	jmpq   *0x200bba(%rip)        # 601020 <rand@GLIBC_2.2.5>
  400466:	68 01 00 00 00       	pushq  $0x1
  40046b:	e9 d0 ff ff ff       	jmpq   400440 <.plt>

Disassembly of section .text:

0000000000400470 <_start>:
  400470:	31 ed                	xor    %ebp,%ebp
  400472:	49 89 d1             	mov    %rdx,%r9
  400475:	5e                   	pop    %rsi
  400476:	48 89 e2             	mov    %rsp,%rdx
  400479:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40047d:	50                   	push   %rax
  40047e:	54                   	push   %rsp
  40047f:	49 c7 c0 60 06 40 00 	mov    $0x400660,%r8
  400486:	48 c7 c1 f0 05 40 00 	mov    $0x4005f0,%rcx
  40048d:	48 c7 c7 47 05 40 00 	mov    $0x400547,%rdi
  400494:	ff 15 56 0b 20 00    	callq  *0x200b56(%rip)        # 600ff0 <__libc_start_main@GLIBC_2.2.5>
  40049a:	f4                   	hlt    
  40049b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000004004a0 <deregister_tm_clones>:
  4004a0:	55                   	push   %rbp
  4004a1:	b8 30 10 60 00       	mov    $0x601030,%eax
  4004a6:	48 3d 30 10 60 00    	cmp    $0x601030,%rax
  4004ac:	48 89 e5             	mov    %rsp,%rbp
  4004af:	74 17                	je     4004c8 <deregister_tm_clones+0x28>
  4004b1:	b8 00 00 00 00       	mov    $0x0,%eax
  4004b6:	48 85 c0             	test   %rax,%rax
  4004b9:	74 0d                	je     4004c8 <deregister_tm_clones+0x28>
  4004bb:	5d                   	pop    %rbp
  4004bc:	bf 30 10 60 00       	mov    $0x601030,%edi
  4004c1:	ff e0                	jmpq   *%rax
  4004c3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4004c8:	5d                   	pop    %rbp
  4004c9:	c3                   	retq   
  4004ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000004004d0 <register_tm_clones>:
  4004d0:	be 30 10 60 00       	mov    $0x601030,%esi
  4004d5:	55                   	push   %rbp
  4004d6:	48 81 ee 30 10 60 00 	sub    $0x601030,%rsi
  4004dd:	48 89 e5             	mov    %rsp,%rbp
  4004e0:	48 c1 fe 03          	sar    $0x3,%rsi
  4004e4:	48 89 f0             	mov    %rsi,%rax
  4004e7:	48 c1 e8 3f          	shr    $0x3f,%rax
  4004eb:	48 01 c6             	add    %rax,%rsi
  4004ee:	48 d1 fe             	sar    %rsi
  4004f1:	74 15                	je     400508 <register_tm_clones+0x38>
  4004f3:	b8 00 00 00 00       	mov    $0x0,%eax
  4004f8:	48 85 c0             	test   %rax,%rax
  4004fb:	74 0b                	je     400508 <register_tm_clones+0x38>
  4004fd:	5d                   	pop    %rbp
  4004fe:	bf 30 10 60 00       	mov    $0x601030,%edi
  400503:	ff e0                	jmpq   *%rax
  400505:	0f 1f 00             	nopl   (%rax)
  400508:	5d                   	pop    %rbp
  400509:	c3                   	retq   
  40050a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400510 <__do_global_dtors_aux>:
  400510:	80 3d 15 0b 20 00 00 	cmpb   $0x0,0x200b15(%rip)        # 60102c <_edata>
  400517:	75 17                	jne    400530 <__do_global_dtors_aux+0x20>
  400519:	55                   	push   %rbp
  40051a:	48 89 e5             	mov    %rsp,%rbp
  40051d:	e8 7e ff ff ff       	callq  4004a0 <deregister_tm_clones>
  400522:	c6 05 03 0b 20 00 01 	movb   $0x1,0x200b03(%rip)        # 60102c <_edata>
  400529:	5d                   	pop    %rbp
  40052a:	c3                   	retq   
  40052b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400530:	f3 c3                	repz retq 
  400532:	0f 1f 40 00          	nopl   0x0(%rax)
  400536:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40053d:	00 00 00 

0000000000400540 <frame_dummy>:
  400540:	55                   	push   %rbp
  400541:	48 89 e5             	mov    %rsp,%rbp
  400544:	5d                   	pop    %rbp
  400545:	eb 89                	jmp    4004d0 <register_tm_clones>

0000000000400547 <main>:
#include <ctime>

const int N = 2000;
const int M = 5000;

int main() {
  400547:	55                   	push   %rbp
  400548:	48 89 e5             	mov    %rsp,%rbp
  40054b:	53                   	push   %rbx
  40054c:	48 83 ec 18          	sub    $0x18,%rsp
    printf("%d %d\n", N, M);
  400550:	ba 88 13 00 00       	mov    $0x1388,%edx
  400555:	be d0 07 00 00       	mov    $0x7d0,%esi
  40055a:	bf 8c 06 40 00       	mov    $0x40068c,%edi
  40055f:	b8 00 00 00 00       	mov    $0x0,%eax
  400564:	e8 e7 fe ff ff       	callq  400450 <printf@plt>
    for (int i = 1; i <= M; i++) printf("%d %d\n", rand() % N + 1, rand() % N + 1);
  400569:	c7 45 ec 01 00 00 00 	movl   $0x1,-0x14(%rbp)
  400570:	81 7d ec 88 13 00 00 	cmpl   $0x1388,-0x14(%rbp)
  400577:	7f 6b                	jg     4005e4 <main+0x9d>
  400579:	e8 e2 fe ff ff       	callq  400460 <rand@plt>
  40057e:	89 c1                	mov    %eax,%ecx
  400580:	ba d3 4d 62 10       	mov    $0x10624dd3,%edx
  400585:	89 c8                	mov    %ecx,%eax
  400587:	f7 ea                	imul   %edx
  400589:	c1 fa 07             	sar    $0x7,%edx
  40058c:	89 c8                	mov    %ecx,%eax
  40058e:	c1 f8 1f             	sar    $0x1f,%eax
  400591:	29 c2                	sub    %eax,%edx
  400593:	89 d0                	mov    %edx,%eax
  400595:	69 c0 d0 07 00 00    	imul   $0x7d0,%eax,%eax
  40059b:	29 c1                	sub    %eax,%ecx
  40059d:	89 c8                	mov    %ecx,%eax
  40059f:	8d 58 01             	lea    0x1(%rax),%ebx
  4005a2:	e8 b9 fe ff ff       	callq  400460 <rand@plt>
  4005a7:	89 c1                	mov    %eax,%ecx
  4005a9:	ba d3 4d 62 10       	mov    $0x10624dd3,%edx
  4005ae:	89 c8                	mov    %ecx,%eax
  4005b0:	f7 ea                	imul   %edx
  4005b2:	c1 fa 07             	sar    $0x7,%edx
  4005b5:	89 c8                	mov    %ecx,%eax
  4005b7:	c1 f8 1f             	sar    $0x1f,%eax
  4005ba:	29 c2                	sub    %eax,%edx
  4005bc:	89 d0                	mov    %edx,%eax
  4005be:	69 c0 d0 07 00 00    	imul   $0x7d0,%eax,%eax
  4005c4:	29 c1                	sub    %eax,%ecx
  4005c6:	89 c8                	mov    %ecx,%eax
  4005c8:	83 c0 01             	add    $0x1,%eax
  4005cb:	89 da                	mov    %ebx,%edx
  4005cd:	89 c6                	mov    %eax,%esi
  4005cf:	bf 8c 06 40 00       	mov    $0x40068c,%edi
  4005d4:	b8 00 00 00 00       	mov    $0x0,%eax
  4005d9:	e8 72 fe ff ff       	callq  400450 <printf@plt>
  4005de:	83 45 ec 01          	addl   $0x1,-0x14(%rbp)
  4005e2:	eb 8c                	jmp    400570 <main+0x29>
    return 0;
  4005e4:	b8 00 00 00 00       	mov    $0x0,%eax
  4005e9:	48 83 c4 18          	add    $0x18,%rsp
  4005ed:	5b                   	pop    %rbx
  4005ee:	5d                   	pop    %rbp
  4005ef:	c3                   	retq   

00000000004005f0 <__libc_csu_init>:
  4005f0:	41 57                	push   %r15
  4005f2:	41 56                	push   %r14
  4005f4:	49 89 d7             	mov    %rdx,%r15
  4005f7:	41 55                	push   %r13
  4005f9:	41 54                	push   %r12
  4005fb:	4c 8d 25 de 07 20 00 	lea    0x2007de(%rip),%r12        # 600de0 <__frame_dummy_init_array_entry>
  400602:	55                   	push   %rbp
  400603:	48 8d 2d de 07 20 00 	lea    0x2007de(%rip),%rbp        # 600de8 <__init_array_end>
  40060a:	53                   	push   %rbx
  40060b:	41 89 fd             	mov    %edi,%r13d
  40060e:	49 89 f6             	mov    %rsi,%r14
  400611:	4c 29 e5             	sub    %r12,%rbp
  400614:	48 83 ec 08          	sub    $0x8,%rsp
  400618:	48 c1 fd 03          	sar    $0x3,%rbp
  40061c:	e8 07 fe ff ff       	callq  400428 <_init>
  400621:	48 85 ed             	test   %rbp,%rbp
  400624:	74 20                	je     400646 <__libc_csu_init+0x56>
  400626:	31 db                	xor    %ebx,%ebx
  400628:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40062f:	00 
  400630:	4c 89 fa             	mov    %r15,%rdx
  400633:	4c 89 f6             	mov    %r14,%rsi
  400636:	44 89 ef             	mov    %r13d,%edi
  400639:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40063d:	48 83 c3 01          	add    $0x1,%rbx
  400641:	48 39 dd             	cmp    %rbx,%rbp
  400644:	75 ea                	jne    400630 <__libc_csu_init+0x40>
  400646:	48 83 c4 08          	add    $0x8,%rsp
  40064a:	5b                   	pop    %rbx
  40064b:	5d                   	pop    %rbp
  40064c:	41 5c                	pop    %r12
  40064e:	41 5d                	pop    %r13
  400650:	41 5e                	pop    %r14
  400652:	41 5f                	pop    %r15
  400654:	c3                   	retq   
  400655:	90                   	nop
  400656:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40065d:	00 00 00 

0000000000400660 <__libc_csu_fini>:
  400660:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400664 <_fini>:
  400664:	48 83 ec 08          	sub    $0x8,%rsp
  400668:	48 83 c4 08          	add    $0x8,%rsp
  40066c:	c3                   	retq   
