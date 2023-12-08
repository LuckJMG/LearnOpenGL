#include "debug.hpp"

#include <iostream>
#include <glm/glm.hpp>

std::ostream& operator<< (std::ostream& out, const glm::vec2& vector) {
	out << "(" << vector.x << ", " << vector.y << ')';
	return out;
}

std::ostream& operator<< (std::ostream& out, const glm::vec3& vector) {
	out << "(" << vector.x << ", " << vector.y << ", " << vector.z << ')';
	return out;
}

std::ostream& operator<< (std::ostream& out, const glm::vec4& vector) {
	out << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ')';
	return out;
}

std::ostream& operator<< (std::ostream& out, const glm::mat2& matrix) {
	out << '[' << matrix[0][0] << ' ' << matrix[0][1] << "]\n";
	out << '|' << matrix[1][0] << ' ' << matrix[1][1] << '|';
	return out;
}

std::ostream& operator<< (std::ostream& out, const glm::mat3& matrix) {
	out << '[' << matrix[0][0] << ' ' << matrix[0][1] << ' ' << matrix[0][2] << "]\n";
	out << '|' << matrix[1][0] << ' ' << matrix[1][1] << ' ' << matrix[1][2] << "|\n";
	out << '|' << matrix[2][0] << ' ' << matrix[2][1] << ' ' << matrix[2][2] << '|';
	return out;
}

std::ostream& operator<< (std::ostream& out, const glm::mat4& matrix) {
	out << '[' << matrix[0][0] << ' ' << matrix[0][1] << ' ' << matrix[0][2] << ' ' << matrix[0][3] << "]\n";
	out << '|' << matrix[1][0] << ' ' << matrix[1][1] << ' ' << matrix[1][2] << ' ' << matrix[1][3] << "|\n";
	out << '|' << matrix[2][0] << ' ' << matrix[2][1] << ' ' << matrix[2][2] << ' ' << matrix[2][3] << "|\n";
	out << '|' << matrix[3][0] << ' ' << matrix[3][1] << ' ' << matrix[3][2] << ' ' << matrix[3][3] << '|';
	return out;
}

