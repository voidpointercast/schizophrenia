/*
 * Attribute.hpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */

#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_

#include<vector>
#include<boost/lexical_cast.hpp>
#include<yaml-cpp/yaml.h>

namespace schizophrenia {

	class Attribute {
		public:
			Attribute(const std::string& name, const std::string& value);
			Attribute(void) = default;
			Attribute(const Attribute& copy) = default;
			virtual ~Attribute();

			bool operator<(const Attribute& right) const;

			bool operator==(const Attribute& right) const;

			YAML::Emitter& operator<<(YAML::Emitter& out) const;

			YAML::Iterator operator>>(YAML::Iterator in);

			template<typename ReturnType=std::string>
			ReturnType getValue(void) const;

			const std::string& getCategory(void) const;

			template<typename InputType=std::string>
			void setValue(const InputType& value);

			template<class Archive>
			void serialize(Archive& archive, const unsigned int version);

			std::string Name;

		protected:
			std::string Value;
			std::string Category;
			std::vector<std::string> Keywords;

};

	template<typename ReturnType>
	ReturnType Attribute::getValue() const {
		return boost::lexical_cast<ReturnType>(this->Value);
	}

	template<typename InputType>
	void Attribute::setValue(const InputType& value) {
		this->Value = boost::lexical_cast<std::string>(value);
	}

	template<class Archive>
	void Attribute::serialize(Archive& archive, const unsigned int version) {
		archive & this->Name;
		archive & this->Value;
		archive & this->Category;
		archive & this->Keywords;
	}


	inline YAML::Emitter& operator<<(YAML::Emitter& out, const Attribute& attribute) {
		return attribute.operator<<(out);
	}

	inline YAML::Iterator operator>>(YAML::Iterator in, Attribute& attribute) {
			return attribute.operator>>(in);
		}

}


#endif /* ATTRIBUTE_HPP_ */
