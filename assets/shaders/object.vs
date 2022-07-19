#version 460
			layout(location = 0) in vec3 vertex_position;
			layout(location = 1) in vec3 normal_vector;
			layout(location = 2) in vec2 texture_position;
			uniform mat4 model_matrix;
			uniform mat4 view_projection_matrix;
			uniform mat3 normal_matrix;
			out vec3 fragment_pos;
			out vec3 normal;
			out vec2 texture_coord;
			void main() {
				normal = mat3(transpose(inverse(model_matrix))) * normal_vector;
				fragment_pos = vec3(model_matrix * vec4(vertex_position, 1.0));
				gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
				texture_coord = texture_position;
			}