#include <iostream>
#include <string.h>
using namespace std;

int main()
{
  char str[10];
  for(int i = 0; i < 10; i++) str[i] = '!';
  cout<<str<<endl;
  sscanf("123456","%s",str);//---------str的值为 "123456\0!!!"
  //这个实验很简单，把源字符串"123456"拷贝到str的前6个字符，并且把str的第7个字符设为null字符，也就是\0
  cout<<str<<endl;

  for(int i = 0; i < 10; i++) str[i] = '!';
  sscanf("123456","%3s",str); //---------str的值为 "123\0!!!!!!"
  //看到没有，正则表达式的百分号后面多了一个3，这告诉sscanf只拷贝3个字符给str，然后把第4个字符设为null字符。
  cout<<str<<endl;

  for(int i = 0; i < 10; i++) str[i] = '!';
  sscanf("aaaAAA","%[a-z]",str);// ---------str的值为 "aaa\0!!!!!!"
  //从这个实验开始我们会使用正则表达式，括号里面的a-z就是一个正则表达式，它可以表示从a到z的任意字符，
  //在继续讨论之前，我们先来看看百分号表示什么意思，%表示选择，%后面的是条件，比如实验1的"%s"，s是一个条件，表示任意字符，"%s"的意思是：只要输入的东西是一个字符，就把它拷贝给str。实验2的"%3s"又多了一个条件：只拷贝3个字符。实验3的“%[a-z]”的条件稍微严格一些，输入的东西不但是字符，还得是一个小写字母的字符，所以实验3只拷贝了小写字母"aaa"给str，别忘了加上null字符。
  cout<<str<<endl;

  for(int i = 0; i < 10; i++) str[i] = '!';
  sscanf("AAAaaaBBB","%[^a-z]",str);// ---------str的值为 "AAA\0!!!!!!"
  //对于所有字符，只要不是小写字母，都满足"^a-z"正则表达式，符号^表示逻辑非。前3个字符都不是小写字符，所以将其拷贝给str，但最后3个字符也不是小写字母，为什么不拷贝给str呢？这是因为当碰到不满足条件的字符后，sscanf就会停止执行，不再扫描之后的字符。
  cout<<str<<endl;

  /*
  for (int i = 0; i < 10; i++) str[i] = '!';
  sscanf("AAAaaaBBB","%[A-Z]%[a-z]",str);// ---------段错误
  //这个实验的本意是：先把大写字母拷贝给str，然后把小写字母拷贝给str，但很不幸，程序运行的时候会发生段错误，因为当sscanf扫描到字符a时，违反了条件"%[A-Z]"，sscanf就停止执行，不再扫描之后的字符，所以第二个条件也就没有任何意义，这个实验说明：不能使用%号两次或两次以上
  cout<<str<<endl;
  */

  for(int i = 0; i < 10; i++) str[i] = '!';
  sscanf("AAAaaaBBB","%*[A-Z]%[a-z]",str); //---------str的值为 "aaa\0!!!!!!"
  //这个实验出现了一个新的符号：%*，与%相反，%*表示过滤满足条件的字符，在这个实验中，%*[A-Z]过滤了所有大写字母，然后再使用%[a-z]把之后的小写字母拷贝给str。如果只有%*，没有%的话，sscanf不会拷贝任何字符到str，这时sscanf的作用仅仅是过滤字符串。
  cout<<str<<endl;

  for(int i = 0; i < 10; i++) str[i] = '!';
  sscanf("AAAaaaBBB","%[a-z]",str);// ---------str的值为 "!!!!!!!!!!"
  //做完前面几个实验后，我们都知道sscanf拷贝完成后，还会在str的后面加上一个null字符，但如果没有一个字符满足条件，sscanf不会在str 的后面加null字符，str的值依然是10个惊叹号。这个实验也说明了，如果不使用%*过滤掉前面不需要的字符，你永远别想取得中间的字符。
  cout<<str<<endl;

  for(int i = 0; i < 10; i++) str[i] = '!';
  sscanf("AAAaaaBC=","%*[A-Z]%*[a-z]%[^a-z=]",str); //---------str的值为 "BC\0!!!!!!!"
  //这是一个综合实验，但这个实验的目的不是帮我们复习前面所学的知识，而是展示两个值得注意的地方：
  //注意1：%只能使用一次，但%*可以使用多次，比如在这个实验里面，先用%*[A-Z]过滤大写字母，然后用%*[a-z]过滤小写字母。
  // 注意2：^后面可以带多个条件，且这些条件都受^的作用，比如^a-z=表示^a-z且^=(既不是小写字母，也不是等于号)。
  cout<<str<<endl;

  for(int i = 0; i < 10; i++) str[i] = '!';
  int k;
  sscanf("AAA123BBB456", "%*[A-Z]%i", &k); //---------k的值为123
  //首先，%*[^0-9]过滤前面非数字的字符，然后用%i把数字字符转换成int型的整数，拷贝到变量k，注意参数必须使用k的地址。    cout<<str<<endl;
  cout<<k<<endl;

  const char src[] = "D:2016-01-04 13:41:48 000000 S:12905 T:2016-01-04 H:3306 L:3250 LP:3305 AP:3305 AV:84 BP:163 BV:3304 OI:506776 V:200342";
  char Dat1[9] ;
  char Time[9] ;
  memset(Dat1,'\0',9);
  memset(Time,'\0',9);

  char 			TradingDay[9];         	///交易日
  char			InstrumentID[31];      	///合约代码
  double 		LastPrice;             	///最新价
  double 		OpenPrice; 				///今开盘
  double 		HighestPrice; 			///最高价
  double 		LowestPrice; 			///最低价
  int 			Volume; 				///数量
  double 		Openinterest; 			///持仓量
  char   		UpdateTime[9]; 			///最后修改时间
  int 			UpdateMillisec; 		///最后修改毫秒
  double 		BidPrice1; 				///申买价一
  int 			BidVolume1; 			///申买量一
  double 		AskPrice1; 				///申卖价一
  int 			AskVolume1; 			///申卖量一
  char			ActionDay[9]; 			///业务日期
  int ss;




  sscanf(src, "D:%s %s %d S:%d T:%s H:%lf L:%lf LP:%lf AP:%lf AV:%d BP:%lf BV:%d OI:%lf V:%d",
         TradingDay,UpdateTime,&UpdateMillisec,&ss,ActionDay,
         &HighestPrice,&LowestPrice,&LastPrice,&AskPrice1,&AskVolume1,&BidPrice1,&BidVolume1,&Openinterest,&Volume); //取需要的字符串

  std::cout << src << endl;
  std::cout << TradingDay <<"t:"<<UpdateTime<<"ms:"<<UpdateMillisec<<"actionda:"<<ActionDay<<"h:"<<HighestPrice<<"l:"<<LowestPrice<<"lp:"<<LastPrice;
  std::cout <<"ap:"<<AskPrice1 <<"av:"<<AskVolume1<<"bp:"<<BidPrice1<<"bv"<<BidVolume1<<"oi:"<<Openinterest<<"v"<<Volume<<endl;


  return 0;
}
