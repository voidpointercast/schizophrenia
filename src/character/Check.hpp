/*
 * Check.hpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */

#ifndef CHECK_HPP_
#define CHECK_HPP_

#include<tuple>
#include<character/BasicTrait.hpp>
#include<character/Attribute.hpp>

namespace schizophrenia {


	template<class Character>
	class Check {
	public:
		enum Action {Remove, Add};
		enum Priority {CoreRule, HouseRoule, SpecialRule, GoldenRule};
		enum Result {Accept, DontCare, Reject};



		Check(const Character& character, Priority priority=CoreRule, unsigned=0);
		virtual ~Check();

		bool operator<(const Check& right) const;

		virtual std::tuple<Result,std::string> operator()(const BasicTrait& trait, Action action) = 0;
		virtual std::tuple<Result,std::string> operator()(const BasicTrait& trait, const std::string& value) = 0;
		virtual std::tuple<Result,std::string> operator()(const BasicTrait& trait, const Attribute& attribute, Action action) = 0;
		virtual std::tuple<Result,std::string> operator()(const BasicTrait& trait, const Attribute& attribute, const std::string& value) = 0;

		const Priority RulePriority;
		const unsigned SubPriority;
		const Character& MonitoredCharacter;

	};

	template<class Character>
	Check<Character>::Check(const Character& character, Priority priority, unsigned subpriority)
	: RulePriority(priority),
	  SubPriority(subpriority),
	  MonitoredCharacter(character){

	}

	template<class Character>
	Check<Character>::~Check() {
	}

	template<class Character>
	bool Check<Character>::operator<(const Check& right) const {
		if(this->RulePriority < right.RulePriority) {
			return true;
		}
		if (this->RulePriority > right.RulePriority) {
			return false;
		}
		return this->SubPriority < right.SubPriority;
	}

} /* namespace schizohrenia */
#endif /* CHECK_HPP_ */
