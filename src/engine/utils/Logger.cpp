#include "Logger.h"

void LittleEngine::Utils::printWarning(const char* string, const char* file, int line)
{
	printf("%s At file: %s, at line: %d\n", string, file, line);
}

void LittleEngine::Utils::printMat4(const glm::mat4 mat)
{
	printf("MAT 4\n");
	printf("[ %f, %f, %f, %f ]\n", mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
	printf("[ %f, %f, %f, %f ]\n", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
	printf("[ %f, %f, %f, %f ]\n", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
	printf("[ %f, %f, %f, %f ]\n", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
}
