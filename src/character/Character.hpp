/*
 * Character.hpp
 *
 *  Created on: Nov 11, 2012
 *      Author: voidpointercast
 */
#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include<vector>
#include<tuple>
#include<memory>
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_generators.hpp>
#include<yaml-cpp/yaml.h>
#include<character/BasicTrait.hpp>
#include<character/Check.hpp>

namespace schizohrenia {

	class Character : public boost::uuids::uuid {
		public:
			typedef typename std::vector<BasicTrait>::const_iterator ConstTraitIterator;
			typedef enum {XML, TEXT} SupportedSerialization;

			Character(void);
			Character(const std::string& type);
			virtual ~Character(void);
//			virtual const std::string& getCharacterType(void) const = 0;
			virtual const std::vector<BasicTrait>& getTraits() const;
			virtual std::tuple<bool,std::string> setValue(const BasicTrait& trait, const std::string& value);
			virtual std::tuple<bool,std::string> setAttribute(const BasicTrait& trait, const Attribute& attribute, const std::string& value);

			virtual std::tuple<bool,std::string> addAttribute(const BasicTrait& trait, const Attribute& attribute);
			virtual std::tuple<bool,std::string> addTrait(const BasicTrait& trait);

			virtual std::tuple<bool,std::string> removeTrait(const BasicTrait& trait);
			virtual std::tuple<bool,std::string> removeAttribute(const BasicTrait&, const Attribute& attribute);

				

			const std::vector<std::shared_ptr<Check<Character>>>& getChecks(void) const;

			std::string getUUID(void) const;

			virtual size_t countTrait(const std::string& traitName) const;

			const BasicTrait& operator[](const std::string& traitName) const;

			YAML::Emitter& operator<<(YAML::Emitter& out) const;

			YAML::Iterator operator>>(YAML::Iterator in);

			void addCheck(const std::shared_ptr<Check<Character>>& check);
			void removeCheck(typename std::vector<std::shared_ptr<Check<Character>>>::iterator position);

			const std::string CharacterType;

			template<class Archive>
			void serialize(Archive& archive, const unsigned int version);

		protected:

			virtual std::tuple<bool,std::string> addAttributeCheck(const BasicTrait& trait, const Attribute& attribute) const;
			virtual std::tuple<bool,std::string> addTraitCheck(const BasicTrait& trait) const;
			virtual std::tuple<bool,std::string> removeTraitCheck(const BasicTrait& trait) const ;
			virtual std::tuple<bool,std::string> removeAttributeCheck(const BasicTrait&, const Attribute& attribute) const;
			virtual std::tuple<bool,std::string> setValueCheck(const BasicTrait& trait, const std::string& value) const ;
			virtual std::tuple<bool,std::string> setAttributeCheck(const BasicTrait& trait, const Attribute& attribute, const std::string& value) const;


			virtual std::ostream& serialize(std::ostream& out, const SupportedSerialization type);


			template<class CheckFunctor>
			std::tuple<bool,std::string> check(CheckFunctor functor) const;

			std::vector<BasicTrait> CharacterTraits;
			std::vector<std::shared_ptr<Check<Character>>> CharacterChecks;

		private:
			std::string ID;




	};

	template<class Archive>
	void Character::serialize(Archive& archive, const unsigned int version) {
		archive & this->CharacterTraits;
	}

	template<class CheckFunctor>
	std::tuple<bool,std::string> Character::check(CheckFunctor functor) const {
		std::vector<std::tuple<Check<Character>::Result,std::string>> checkResults{this->CharacterChecks.size()};
		auto begin 	= this->CharacterChecks.begin();
		auto end	= this->CharacterChecks.end();
		auto out	= checkResults.rbegin();
		auto cbegin = checkResults.begin();
		auto cend	= checkResults.end();

		std::transform(begin,end,out,[&](const std::shared_ptr<Check<Character> >& check) -> std::tuple<Check<Character>::Result,std::string> { return functor(check);});
		auto result = std::find_if(cbegin,cend,[](const std::tuple<Check<Character>::Result,std::string>& result) -> bool { return std::get<0>(result) != Check<Character>::Result::DontCare;});
		if(result == cend) {
			return std::make_tuple(true,"No objections");
		}
		return std::make_tuple(std::get<0>(*result) == Check<Character>::Result::Accept,std::get<1>(*result));
	}


	inline YAML::Emitter& operator<<(YAML::Emitter& out, const Character& character) {
		return character.operator<<(out);
	}

	inline YAML::Iterator operator>>(YAML::Iterator in, Character& character) {
		return character.operator>>(in);
	}


}
#endif
