#pragma once

#include <stdexcept>
#include <string>

namespace cppcrudbp::domain {

/**
 * @brief Base class for domain-specific exceptions.
 * Inherits from std::runtime_error.
 */
class DomainException : public std::runtime_error {
public:
  explicit DomainException(const std::string &message)
      : std::runtime_error(message) {}
};

/**
 * @brief Exception thrown when an entity is not found.
 */
class NotFoundException : public DomainException {
public:
  explicit NotFoundException(const std::string &message)
      : DomainException(message) {}
};

/**
 * @brief Exception thrown when a duplicate entity is encountered (e.g., unique
 * constraint violation).
 */
class DuplicateEntryException : public DomainException {
public:
  explicit DuplicateEntryException(const std::string &message)
      : DomainException(message) {}
};

/**
 * @brief Exception thrown for general database errors.
 */
class DatabaseException : public DomainException {
public:
  explicit DatabaseException(const std::string &message)
      : DomainException(message) {}
};

} // namespace cppcrudbp::domain
