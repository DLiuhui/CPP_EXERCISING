///
/// @file    booksale.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-04 23:54:15
///

#ifndef BOOKSALE_H_
#define BOOKSALE_H_
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <map>
#include <set>

namespace Primer
{
	//基类
	class Quote
	{
		public:
			Quote() = default;
			Quote(const Quote &) = default;
			Quote(Quote &&) = default;
			Quote & operator=(const Quote &) = default;
			Quote & operator=(Quote &&) = default;
			Quote(const std::string &book, double sales_price = 0.0):
				_price(sales_price), _bookNo(book)
			{}
			std::string isbn() const {return _bookNo;}
			//返回给定数量书籍的销售总额
			//派生类负责改写并使用不同的折扣计算方法
			virtual double net_price(std::size_t n) const
			{
				return n * _price;
			}
			virtual ~Quote() = default;	//对析构函数进行动态绑定
			virtual Quote *clone() const &
			{
				return new Quote(*this);
			}
			virtual Quote *clone() &&
			{
				return new Quote(std::move(*this));
			}
		protected:
			double _price;
		private:
			std::string _bookNo;
	};
	double print_total(std::ostream &os, const Quote &item, std::size_t n)
	{
		//根据传入item形参的对象类型调用Quote或者BulkQuote版本的
		//net_price函数
		//BulkQuote会隐式类型转换成Quote
		double ret = item.net_price(n);
		os << "ISBN:" << item.isbn() << "# sold:" << n << " total due:" << ret << std::endl;
		return ret;
	}

	//抽象基类
	class DiscQuote : public Quote
	{
		public:
			DiscQuote() = default;
			DiscQuote(const std::string &book, double price, std::size_t qty, double disc):
				Quote(book, price), _quantity(qty), _discount(disc)
			{}
			std::pair<std::size_t, double> discount_policy() const	//查看折扣策略
			{ return {_quantity, _discount}; }
			double net_price(std::size_t) const = 0;	//纯虚函数
		protected:
			std::size_t _quantity = 0;	//折扣适用的购买量
			double _discount = 0.0;	//表示折扣的小数值
	};

	//派生类
	//当同一书籍的销售量超过某个值时启用折扣
	//折扣值是小于1的正小数
	class BulkQuote : public DiscQuote
	{
		public:
			BulkQuote() = default;
			BulkQuote(const std::string &, double, std::size_t, double);
			//覆盖基类的函数版本以实现基于大量购买的折扣策略
			double net_price(std::size_t) const override;
			BulkQuote *clone() const & override
			{return new BulkQuote(*this);}
			BulkQuote *clone() && override
			{
				return new BulkQuote(std::move(*this));
			}
	};
	BulkQuote::BulkQuote(const std::string &book, double price, std::size_t qty, double disc):
		DiscQuote(book, price, qty, disc)
	{}
	double BulkQuote::net_price(std::size_t cnt) const
	{
		if(cnt >= _quantity)
			return cnt * (1 - _discount) * _price;	//_price是受保护类，可以由派生类访问
		else
			return cnt * _price;
	}

	class Basket
	{
		public:
			void add_item(const Quote &sale)
			{
				items.insert(std::shared_ptr<Quote>(sale.clone()));
			}
			void add_item(Quote &&sale)
			{
				items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
			}
			double total_receipt(std::ostream &) const;
		private:
			static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs)
			{ return lhs->isbn() < rhs->isbn();}
			std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};	//第二个类型实例化 比较函数类型，items初始化需要使用compare作为参数
	};

	double Basket::total_receipt(std::ostream &os) const
	{
		double sum = 0.0;
		for(auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
		{
			sum += print_total(os, **iter, items.count(*iter));
		}
		os << "Total Sale:" << sum << std::endl;
		return sum;
	}
}


#endif
