/*
 * BasicTrait.hpp
 *
 *  Created on: Nov 11, 2012
 *      Author: voidpointercast
 */

#ifndef BASICTRAIT_HPP_
#define BASICTRAIT_HPP_
#include<vector>
#include<iostream>
#include<string>
#include<memory>
#include<algorithm>
#include<boost/lexical_cast.hpp>
#include<yaml-cpp/yaml.h>
#include<character/Attribute.hpp>

namespace schizohrenia {

	struct BasicTrait {
	public:
		BasicTrait(const std::string& name, const std::string& value);
		template<class InputIterator>
		BasicTrait(const std::string& name, const std::string& value, InputIterator begin, InputIterator end);
		BasicTrait(const BasicTrait& copy) = default;
		BasicTrait(void) = default;
		virtual ~BasicTrait() throw();
		bool operator<(const BasicTrait& right) const;
		bool operator==(const BasicTrait& right) const;
		bool operator==(const std::string& right) const;
		bool hasAttribute(const std::string& attribute) const;

		YAML::Emitter& operator<<(YAML::Emitter& out) const;
		YAML::Iterator operator>>(YAML::Iterator in);

		template<class Archive>
		void serialize(Archive& archive, const unsigned int version=0);

		template<class ReturnType>
		ReturnType getValue(void) const;

		void save(std::ostream& out) const;

		std::string					Value;
		std::vector<Attribute>	 	Attributes;
		std::string 				Name;
	};

	template<class Archive>
	void BasicTrait::serialize(Archive& archive, const unsigned int version) {
		archive & this->Name;
		archive & this->Attributes;
		archive & this->Value;
	}

	template<class InputIterator>
	BasicTrait::BasicTrait(const std::string& name, const std::string& value, InputIterator begin, InputIterator end)
	: Name(name), Value(value), Attributes(begin,end) {

	}

	template<class ReturnType>
	ReturnType BasicTrait::getValue(void) const {
		return boost::lexical_cast<ReturnType>(this->Value);
	}

	inline YAML::Emitter& operator<<(YAML::Emitter& out, const BasicTrait& trait) {
		return trait.operator <<(out);
	}

	inline YAML::Iterator operator>>(YAML::Iterator in, BasicTrait& trait) {
		return trait.operator >>(in);
	}

}
#endif
