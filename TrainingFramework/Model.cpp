#include "stdafx.h"
#include "Model.h"
#include "Vertex.h"

Model::Model() {};

Model::~Model() {};

Model::Model(const char* strModelFileName) {
	FILE* file = fopen(strModelFileName, "r");
	
	Vertex* verticesData = nullptr;
	int* indicesData = nullptr;
	int numVertices;
	
	fscanf(file, "NrVertices: %d\n", &numVertices);

	verticesData = new Vertex[numVertices];

	for (int i = 0; i < numVertices; i++) {
		fscanf(file, "%*d. pos: [%f, %f, %f] ; norm: [%*f, %*f, %*f] ; binorm: [%*f, %*f, %*f] ; tgt: [%*f, %*f, %*f] ; uv: [%f, %f] ;\n",
			&verticesData[i].pos.x, &verticesData[i].pos.y, &verticesData[i].pos.z, 
			&verticesData[i].uv.x, &verticesData[i].uv.y);
		
		verticesData[i].pos.y -= 1.0f;
	}

	fscanf(file, "NrIndices: %d\n", &m_numIndices);

	indicesData = new int[m_numIndices];

	for (int i = 0; i < m_numIndices; i += 3) {
		fscanf(file, "%*d.     %d,    %d,    %d\n", &indicesData[i], &indicesData[i + 1], &indicesData[i + 2]);
	}

	fclose(file);

	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(int), indicesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete verticesData;
	delete indicesData;
};

GLuint Model::getVboId() {
	return m_vboId;
};

GLuint Model::getIboId() {
	return m_iboId;
};

GLuint Model::getNumIndices() {
	return m_numIndices;
};