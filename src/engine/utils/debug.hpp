#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <glm/glm.hpp>

std::ostream& operator<< (std::ostream& out, const glm::vec2& vector);
std::ostream& operator<< (std::ostream& out, const glm::vec3& vector);
std::ostream& operator<< (std::ostream& out, const glm::vec4& vector);

std::ostream& operator<< (std::ostream& out, const glm::mat2& matrix);
std::ostream& operator<< (std::ostream& out, const glm::mat3& matrix);
std::ostream& operator<< (std::ostream& out, const glm::mat4& matrix);

#endif
