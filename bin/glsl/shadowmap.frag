#define PI 3.14159265358979323846

uniform sampler2D texture;
uniform vec2 resolution;

void main(void)
{
	bool hasHitWall = false;
	float distance = 1.0;

	for (float y= 0.0; y < resolution.y; y += 1.0)
	{
		vec2 normal = vec2(gl_TexCoord[0].s, y / resolution.y) * 2.0 - 1.0;
		float theta = PI * 1.5 + normal.x * PI;
		float r = (1.0 + normal.y) * 0.5;

		vec2 occlusionMapCoords = vec2(-r * sin(theta), -r * cos(theta)) / 2.0 + 0.5;
		vec4 data = texture2D(texture, occlusionMapCoords);
		if(!hasHitWall && data.a > 0.)
		{
			hasHitWall = true;
		}
		if(hasHitWall && data.a == 0.)
		{
			distance = min(distance, y / resolution.y);
			break;
		}
	}

	gl_FragColor = vec4(vec3(distance), 1.0);
}
