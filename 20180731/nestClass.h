///
/// @file    netClass.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 18:07:58
///

#ifndef NESTCLASS_H_
#define NESTCLASS_H_

//嵌套类的高级用法:
////PIMPL设计模式:
////1. 实现信息隐藏
////2. 接口与实现进行分离
////3. 减小编译依赖
////4. 能够以最小的代价，实现库的平滑升级

class Line
{
	class LineImpl;	//实现line功能的类
public:
	Line(int,int,int,int);
	~Line();
	void printLine() const;
private:
	LineImpl *_pimpl;
};

#endif
