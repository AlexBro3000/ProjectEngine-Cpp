#include <glm/gtc/type_ptr.hpp>
#include <type_traits>

template<class>
inline constexpr bool always_false = false;

template<typename T>
void ShaderProgram::setUniform(const std::string& name, const T& value) const
{
    GLint location = getUniformLocation(name);
    if (location != -1) {
		if constexpr (std::is_same_v<T, float>) {
            glUniform1f(location, value);
		}
		//else if constexpr (std::is_same_v<T, glm::vec1>) {
		//	glUniform1f(location, value.x);
		//}
		//else if constexpr (std::is_same_v<T, glm::vec2>) {
		//	glUniform2f(location, value.x, value.y);
		//}
		//else if constexpr (std::is_same_v<T, glm::vec3>) {
		//	glUniform3f(location, value.x, value.y, value.z);
		//}
		//else if constexpr (std::is_same_v<T, glm::vec4>) {
		//	glUniform4f(location, value.x, value.y, value.z, value.w);
		//}
		else if constexpr (std::is_same_v<T, int>) {
			glUniform1i(location, value);
		}
		//else if constexpr (std::is_same_v<T, glm::ivec1>) {
		//	glUniform1i(location, value.x);
		//}
		//else if constexpr (std::is_same_v<T, glm::ivec2>) {
		//	glUniform2i(location, value.x, value.y);
		//}
		//else if constexpr (std::is_same_v<T, glm::ivec3>) {
		//	glUniform3i(location, value.x, value.y, value.z);
		//}
		//else if constexpr (std::is_same_v<T, glm::ivec4>) {
		//	glUniform4i(location, value.x, value.y, value.z, value.w);
		//}
        else if constexpr (std::is_same_v<T, glm::vec3>) {
            glUniform3fv(location, 1, glm::value_ptr(value));
        }
        else if constexpr (std::is_same_v<T, glm::mat4>) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
        }
		else {
			static_assert(always_false<T>, "Unsupported uniform type!");
		}
	}
}
