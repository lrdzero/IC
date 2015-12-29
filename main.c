#include <stdio.h>
#include "fb_rna.h"
#define USE_MNIST_LOADER
#define MNIST_DOUBLE
#include "mnist.h"

void main (void)
{
	int aciertos=0;
	mnist_data *entrena,*test;
        unsigned int cnt,cnt2;
        int ret,ret2;

        if (ret = mnist_load("train-images.idx3-ubyte", "train-labels.idx1-ubyte", &entrena, &cnt)) {
                printf("An error occured: %d\n", ret);
        } else {
                printf("image count: %d\n", cnt);

                //free(entrena);
        }

if (ret2 = mnist_load("t10k-images.idx3-ubyte", "t10k-labels.idx1-ubyte", &test, &cnt2)) {
                printf("An error occured: %d\n", ret2);
        } else {
                printf("image count: %d\n", cnt2);

                //free(test);
        }

  float     error;
  NeuralNet nn = CreaRNA(28*28,100,10,0.1,PEsigmoid,DerivPEsigmoid);

  InicializarPesosRNA(nn);
	
  for(int i=0;i<40000;i++){
	for(int j=0;j<28;j++){
		for(int z=0;z<28;z++){
			ENTRADA(nn,(j*28)+z)=entrena[i].data[j][z];
			if(entrena[i].data[j][z]>0.65){
				RESULTADO_DESEADO(nn,(j*28)+z)=1;
			}
			else{
				RESULTADO_DESEADO(nn,(j*28)+z)=0;
			}
		}
	}
	error=LearnRNA(nn);
	
  }
for(int i=0;i<8000;i++){
	for(int j=0;j<28;j++){
		for(int z=0;z<28;z++){
			ENTRADA(nn,(j*28)+z)=test[i].data[j][z];
			if(test[i].data[j][z]>0.65){
				RESULTADO_DESEADO(nn,(j*28)+z)=1;
			}
			else{
				RESULTADO_DESEADO(nn,(j*28)+z)=0;
			}
		}
	}
	
	TestRNA(nn);
	//printf("%d\n",test[i].label);
	double max=0.00000;
	int valor = 0;
	
	for(int g=0;g<10;g++){
		if(max<SALIDA(nn,g)){
			max=SALIDA(nn,g);
			valor=g;
		}
		
	}	
	if(test[i].label==valor){
		aciertos++;
	}
	
	
  }
  printf("Acierto %d\n",aciertos);



}
