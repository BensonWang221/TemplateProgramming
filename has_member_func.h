// 判断一个class/struct是否含有xxx成员函数

#include <type_traits>

#define HAS_MEMBER(XXX) \
template<typename T, typename... Args>\
struct has_member_##XXX \
{ \
private:  \
  template<typename U> static auto Check(int) -> decltype(std::declval<U>().XXX(std::declval<Args>()...), std::true_type());  \
  template<typename U> static std::false_type Check(...); \
public: \
  static constexpr auto value = decltype(Check<T>(0))::value; \
}

// 第一个Check要有int参数，下面调用处传入0的原因：
// 如果没有int(即无参), 下面不传入0的话，则满足第一个时两个Check的匹配优先级相同，编译会报错ambiguous，
// 加上这些的话，如果满足第一个则匹配第一个，不满足则第二个

/* Usage example:
HAS_MEMBER(foo);

class A {
    public:
        int a;
        void foo(int ,double) {}
};

template <class T>
typename std::enable_if<has_member_foo<T, int>::value, void>::type check() {
    std::cout << "Has" << std::endl;
}
template <class T>
typename std::enable_if<!has_member_foo<A, int>::value, void>::type check() {
    std::cout << "Not Has" << std::endl;
}

*/
