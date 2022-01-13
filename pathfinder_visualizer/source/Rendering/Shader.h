#pragma once

#include <string>
#include <unordered_map>

#include "glm/matrix.hpp"

class Shader
{
public:

	Shader(const std::string& filepath);
    ~Shader();

	void bind() const;
    void unbind() const;
    void set_uniform4f(const std::string& name, float v1, float v2, float v3, float v4) const;
    void set_uniform1i(const std::string& name, int v1) const;
    void set_uniform_mat4f(const std::string& name, const glm::mat4& matrix) const;

private:

    struct shader_source
    {
        std::string vertex_source;
        std::string fragment_source;
    };

    unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);
    unsigned int compile_shader(unsigned int type, const std::string& source);
    shader_source parse_shader(const std::string& filepath);
    int get_uniform_location(const std::string& name) const;

    std::string m_file_path;
    unsigned int m_shader_id;
    std::unordered_map<std::string, int> m_uniform_location_cache;

};
