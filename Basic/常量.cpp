// 宏常量
#define Day 7
// const修饰变量
const int Day_const = 7;
/**
* C++中#define宏常量与const修饰变量的主要区别如下：

‌处理阶段与机制‌

宏常量在‌预处理阶段‌进行文本替换，编译器不会识别其为变量，仅作为字面值展开‌。
const变量在‌编译阶段‌处理，具有明确的变量属性（如数据类型、内存地址等）‌。
‌类型检查与安全性‌

宏常量‌无类型检查‌，直接替换可能导致类型错误或意外副作用（例如表达式替换引发计算错误）‌。
const变量有严格的数据类型（如const int），编译器会进行类型检查，避免潜在错误‌。
‌作用域与生命周期‌

宏常量‌无作用域限制‌，通常定义在文件顶部，全局有效且易与其他标识符冲突‌。
const变量遵循块作用域或命名空间作用域规则，可定义在函数内部或特定作用域内，避免全局污染‌。
‌调试与内存分配‌

宏常量不占用内存，但调试时无法追踪符号（仅显示替换后的字面值）‌。
const变量可能分配内存（除非编译器优化为常量折叠），支持调试器查看符号信息‌。
‌兼容性与扩展功能‌

宏常量支持条件编译（如#ifdef）和字符串化操作，但缺乏类型安全‌。
const变量可配合constexpr（C++11起）实现编译时计算，更适合现代C++的类型安全和性能优化‌。
*/