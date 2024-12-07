#include "core.h"
#include <functional>
#include <iostream>
#include <map>

core::DayFactory &core::DayFactory::instance() {
  static DayFactory factory;
  return factory;
}

void core::DayFactory::registerDay(const std::string &day, Creator creator) {
  creators_[day] = std::move(creator);
}

core::Day *core::DayFactory::createDay(const std::string &day) {
  if (const auto it = creators_.find(day); it != creators_.end()) {
    return it->second();
  }
  return nullptr;
}

core::Day *core::loadDayInstance(const std::string &day) {
  return DayFactory::instance().createDay(day);
}

core::DayRegistrar::DayRegistrar(const std::string &day,
                                 const DayFactory::Creator &creator) {
  DayFactory::instance().registerDay(day, creator);
}