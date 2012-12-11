/*
 * PowerStatCheck.hpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */

#ifndef POWERSTATCHECK_HPP_
#define POWERSTATCHECK_HPP_

#include<character/Check.hpp>
#include<character/Character.hpp>

namespace schizohrenia {


class PowerStatCheck: public schizohrenia::Check<Character> {
public:
	PowerStatCheck(const Character& character);
	virtual ~PowerStatCheck();

	virtual std::tuple<Check<Character>::Result,std::string> operator()(const BasicTrait& trait, Action action);
	virtual std::tuple<Check<Character>::Result,std::string> operator()(const BasicTrait& trait, const std::string& value);
	virtual std::tuple<Check<Character>::Result,std::string> operator()(const BasicTrait& trait, const Attribute& attribute, Action action);
	virtual std::tuple<Check<Character>::Result,std::string> operator()(const BasicTrait& trait, const Attribute& attribute, const std::string& value);

protected:
	unsigned short 	PowerStatValue;
	size_t			PowerStatCount;

	virtual bool checkTraitBounds(const BasicTrait& trait) const;



};

} /* namespace schizohrenia */
#endif /* POWERSTATCHECK_HPP_ */
