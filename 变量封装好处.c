加了封装后，至少可以知道别人在什么地方修改了我的变量。

1. 能不用全局变量尽量不用，我想除了系统状态和控制参数、通信处理和一些需要效率的模块，其他的基本可以靠合理的软件分层和编程技巧来解决。

2. 如果不可避免需要用到，那能藏多深就藏多深。

1)如果只有某.c文件用，就static到该文件中，顺便把结构体定义也收进来；

2)如果只有一个函数用，那就static到函数里面去；

3)如果非要开放出去让人读取，那就用函数return出去，这样就是只读属性了；

4)如果非要遭人蹂躏赋值，好吧，我开放函数接口让你传参赋值；

5)实在非要extern**我，我还可以严格控制包含我.h档的对象，而不是放到公共的includes.h中被人围观，丢人现眼。

如此，你可明白我对全局变量的感悟有多深刻。悲催的我，已经把当年那些“老人”交给我维护的那些案子加班全部重新翻写了。你能明白吗，不要让人背后唾弃你哦。

比如像用于配置的“参数”类的变量， 一般情况下这类模块中的变量会比较多。
这种情况，如果单独封装每个变量的访问API接口，肯定不现实（接口太多了， 不符合模块接口尽量简单化原则）。
可以采用类似于stm32库函数的做法， 对这些参数进行打包封装为“结构体变量”类型， 并在h文件中导出。
在c文件中把这个参数定义为static类型（静态变量）， 并实现读/写接口函数。

// 模块接口h文件中：
typedef struct {
  Param_A;
  Param_B;
  Param_C;
} User_Param_Typedef;

bool ModuleName_SetParam(User_Param_Typedef *param);
bool ModuleName_GetParam(User_Param_Typedef *param);

复制代码

// 模块实现c文件中：
static User_Param_Typedef user_param;
static bool user_access_locked;

bool ModuleName_SetParam(User_Param_Typedef *param)
{
  // 此处还可以增加对参数的保护特性
  user_param.Param_A = param->Parma_A;
  user_param.Param_B = param->Parma_B;
  user_param.Param_C = param->Parma_C;
  return true;
}

bool ModuleName_GetParam(User_Param_Typedef *param)
{
  // 此处还可以增加对参数的保护特性
  param->Param_A = user_param.Parma_A;
  param->Param_B = user_param.Parma_B;
  param->Param_C = user_param.Parma_C;
  return true;
}
复制代码

// app文件中：

...
// 配置参数
User_Param_Typedef  user_param;    // 临时变量（局部变量 ） 或 静态变量
user_param.Param_A = 1;
user_param.Param_B = 2;
user_param.Param_C = 3;
ModuleName_SetParam(&user_param);
...

// 获取参数
ModuleName_GetParam(&user_param);

复制代码


如果在应用中， 仅需要修改其中一个参数怎么办呢？  其实很简单， 根据上面的类似的方法修改， 增加基于 “基地址偏移量” 读/写的接口函数即可。