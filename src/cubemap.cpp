#include <texture/cubemap.hpp>
#include <iostream>
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utils/utils.hpp>

CubeMap::CubeMap(){
    float* skyBoxVertices = CubeMapUtils::getVertices();
    int* skyBoxIndices = CubeMapUtils::getIndices();
    std::string facesCubemap[6] = {
        "../resource/nx.png",
        "../resource/px.png",
        "../resource/py.png",
        "../resource/ny.png",
        "../resource/nz.png",
        "../resource/pz.png"
	};

	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    for (unsigned int i = 0; i < 6; i++){
	    int width, height, nrChannels;
	    unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
	    if (data){
	    	stbi_set_flip_vertically_on_load(false);
	    	glTexImage2D(
	    		GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
	    		0,
	    		GL_RGB,
	    		width,
	    		height,
	    		0,
	    		GL_RGB,
	    		GL_UNSIGNED_BYTE,
	    		data
	    	);
	    	stbi_image_free(data);
	    }
	    else{
	    	std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
	    	stbi_image_free(data);
	    }
	}
}

void CubeMap::activate(){
}

void CubeMap::bind(){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
}




