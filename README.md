
1- Collect N_Samples Vector from sound card 
2- Appli window function to N_Samples Vector (Hann aka Hanning window)
3- Set a ComplexVector ( Real = N_Samples , Img = 0)
4- Appli FFT(ComplexVector)

5- Set peak frequencies in the spectrum array
 for(j = 0; j ＜(N/2)    ; j++){
  magnitude = sqrt( ComplexVector[j].re^2+ ComplexVector[j].img^2);
  freq      =  j * SampleRate /N;
  for( i=0;i＜BUCKETS;i++){
   if( freq＞=Freq_Bin[i] && freq＜=Freq_Bin[i+1] ){
    if (magnitude ＞ Spectrum[i]){
     Spectrum[i] = magnitude;
    }
   }
  }
 }
Freq_Bin: is a distribution of audible frequencies

6- If you want appli Spectrum deformations f(x)

Spectrum[i]= f( Spectrum[i] )

Natural
f(x)=x*Fit_factor

Exponential
f(x)=log(x*Fit_factor2)*Fit_factor

Multi Peak Scale
f(x,i)=x/Peak[i]*Fit_factor

Max Peak Scale
f(x)=x/Global_Peak*Fit_factor

7- Render spectrum magnitudes (Spectrum[i])
