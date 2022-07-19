#version 460
			uniform vec3 view_pos;
			in vec3 normal;
			in vec3 fragment_pos;
			in vec2 texture_coord;
			out vec4 frag_color;

			struct Material {
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				float shininess;
			};

			struct DirectionalLight {
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				vec3 direction;
			};

			struct PointLight
			{
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				vec3 position;
				vec3 attenuation;
			};

			struct SpotLight
			{
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				vec3 position;
				vec3 direction;
				vec3 attenuation;
				float inner_cutoff;
				float outer_cutoff;
			};

			uniform Material material;
			uniform DirectionalLight directional_light;
			//uniform PointLight point_light;
			//uniform SpotLight spot_light;

			uniform sampler2D texture_data;

			void main() {
				//vec3 light_direction = normalize(spot_light.position - fragment_pos);
				vec3 light_direction = -directional_light.direction;
				float theta = dot(light_direction, normalize(-directional_light.direction));
				//float epsilon = spot_light.inner_cutoff - spot_light.outer_cutoff;
				//float intensity = clamp((theta - spot_light.outer_cutoff) / epsilon, 0.0, 1.0);
				//float distance = length(spot_light.position - fragment_pos);
				//float att = 1.0 / (spot_light.attenuation.x + spot_light.attenuation.y * distance + spot_light.attenuation.z * (distance * distance));   
				vec3 ambient = material.ambient * directional_light.ambient;
				/*if(theta > spot_light.outer_cutoff)
				{
					float diff = max(dot(normal, light_direction), 0.0);
					vec3 diffuse = (diff * material.diffuse) * spot_light.diffuse;

					vec3 view_direction = normalize(view_pos - fragment_pos);
					vec3 reflect_direction = reflect(-light_direction, normal); 
					float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
					vec3 specular = (spec * material.specular) * spot_light.specular;

					diffuse *= att;
					specular *= att;

					diffuse *= intensity;
					specular *= intensity;

					frag_color = vec4(ambient + diffuse + specular, 1.0) * texture(texture_data, texture_coord);
				}*/
					float diff = max(dot(normal, light_direction), 0.0);
					vec3 diffuse = (diff * material.diffuse) * directional_light.diffuse;

					vec3 view_direction = normalize(view_pos - fragment_pos);
					vec3 reflect_direction = reflect(-light_direction, normal); 
					float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
					vec3 specular = (spec * material.specular) * directional_light.specular;

					//diffuse *= att;
					//specular *= att;

					//diffuse *= intensity;
					//specular *= intensity;

					frag_color = vec4(ambient + diffuse + specular, 1.0) * texture(texture_data, texture_coord);
				/*else
				{
					frag_color = vec4(ambient, 1.0) * texture(texture_data, texture_coord);
				}*/
			}