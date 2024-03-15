#pragma once

class mat4x4
{
public:
	mat4x4()
	{
	}

	static mat4x4 identity()
	{
		mat4x4 output;

		for (int i = 0; i < 4; i++)
		{
			output.mat[i][i] = 1;
		}

		return output;
	}

	inline float* operator[](int index)
	{
		return mat[index];
	}

	float determinant()
	{

	}

	void orthoLH(float i_width, float i_height, float i_nearPlane, float i_farPlane)
	{
		mat[0][0] = 2.0f / i_width;
		mat[1][1] = 2.0f / i_height;
		mat[2][2] = 1.0f / (i_farPlane - i_nearPlane);
		mat[3][2] = -(i_nearPlane / (i_farPlane - i_nearPlane));
	}

	float mat[4][4];
};
