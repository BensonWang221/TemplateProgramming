// 检测某个class/struct是否含有xxx成员/成员函数
#include <type_traits>

#define HAS_MEMBER(xxx) \
template <class T> \
struct has_member_##xxx \
{ \
    template <class U> \
    static void check(decltype(&U::xxx)); \
    template <class U> \
    static int check(...); \
    static constexpr auto value = std::is_void<decltype(check<T>(0))>::value; \
}

/* Usage example:
HAS_MEMBER(foo);

class A {
    public:
        int foo;
};

template <class T>
typename std::enable_if<has_member_foo<T>::value, void>::type check() {
    std::cout << "Has" << std::endl;
}
template <class T>
typename std::enable_if<!has_member_foo<T>::value, void>::type check() {
    std::cout << "Not Has" << std::endl;
}
*/
