
/*
如何查看反汇编？
打断点 F5调试后
调试窗口输入：-exec disassemble /m
或者-exec disassemble /m main
-exec info registers
得到寄存器的信息
*/

class Point
{
public:
    int nx,ny,nTest;
    Point(int x, int y) 
    {
        nx = x;
        ny = y;
        nTest = nx + ny;
    }
    ~Point() = default;
};

// "__cdecl" : C Declaration，参数从右向左入栈，"主调函数"负责栈平衡。C的标准调用方式，可变参数的函数只能使用该调用约定，比如"printf"
// 由于每一个使用__cdecl约定的函数都要包含清理堆栈的代码，所以产生的可执行文件大小会比较大。
// 编译后的函数名：Fun1(int, int):
void __cdecl Fun1(int x, int y)
{
    Point pt(0,0);
    pt.nx = x;
    pt.ny = y;
    // ret    注意，这里没有值
}

// "__fastcall": 所谓快速，这种方式选择将参数优先从寄存器传入（ECX和EDX），剩下的参数再从右向左从栈传入。因为栈是位于内存的区域，而寄存器位于CPU内，故存取方式快于内存，故其名曰“__fastcall”。
void __fastcall Fun2(int x, int y)
{
    Point pt(0,0);
    pt.nx = x;
    pt.ny = y;
}

// "__stdcall" : Standard Call，windows API默认方式，参数从右向左入栈，"被调函数"负责栈平衡。C++的标准调用方式， 入参个数固定
// 编译后的函数名：_Z4Fun3ii@8:
void __stdcall Fun3(int x, int y)
{
    Point pt(0,0);
    pt.nx = x;
    pt.ny = y;
    /*
    ret    0x8   “自动清栈”体现在这里：ret指令后面跟没跟值就决定了函数返回是栈指针ESP需要增加的量。
    */
}

int main() {
    Fun1(2,5); // __cdecl, 主调函数， 手动清栈
    Fun2(2,5); // __fastcall
    Fun3(2,5); // __stdcall, 被调函数, 自动清栈
}