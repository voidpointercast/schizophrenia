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

namespace schizophrenia {

	struct BasicTrait {
	public:
		BasicTrait(const std::string& name, const std::string& value);
		BasicTrait(const std::string& id, const std::string& name, const std::string& value);
		template<class InputIterator>
		BasicTrait(const std::string& name, const std::string& value, InputIterator begin, InputIterator end);
		template<class InputIterator>
		BasicTrait(const std::string& id, const std::string& name, const std::string& value, InputIterator begin, InputIterator end);
		BasicTrait(const BasicTrait& copy) = default;
		BasicTrait(void) = default;
		virtual ~BasicTrait();
		bool operator<(const BasicTrait& right) const;
		bool operator==(const BasicTrait& right) const;
		bool operator==(const std::string& right) const;
		bool hasAttribute(const std::string& attribute) const;
		bool hasAttribute(const Attribute& attribute) const;
		YAML::Emitter& operator<<(YAML::Emitter& out) const;
		YAML::Iterator operator>>(YAML::Iterator in);

		template<class Archive>
		void serialize(Archive& archive, const unsigned int version=0);

		template<class ReturnType>
		ReturnType getValue(void) const;

		void save(std::ostream& out) const;

		std::string					Value;
		std::vector<Attribute>	Attributes;
		std::string 				Name;
		std::string					ID;
	};

	template<class Archive>
	void BasicTrait::serialize(Archive& archive, const unsigned int version) {
		archive & this->ID;
		archive & this->Name;
		archive & this->Attributes;
		archive & this->Value;
	}

	template<class InputIterator>
	BasicTrait::BasicTrait(const std::string& name, const std::string& value, InputIterator begin, InputIterator end)
	: ID(name), Name(name), Value(value), Attributes(begin,end) {

	}
	
	template<class InputIterator>
	BasicTrait::BasicTrait(const std::string& id, const std::string& name, const std::string& value, InputIterator begin, InputIterator end)
	: ID(id), Name(name), Value(value), Attributes(begin,end) {
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
