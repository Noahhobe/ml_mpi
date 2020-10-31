#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct distance_metric {
  unsigned id;
  double distance;
};

/*comparator that sorts lowest to highest*/
int sortLess(const void *ap, const void *bp){
 struct distance_metric const a = *((struct distance_metric*)ap);
 struct distance_metric const b = *((struct distance_metric*)bp);

 if(a.distance < b.distance){
  return -1;
}
 else if(a.distance == b.distance){
  return 0;
}
 else{
  return 1;
}
}

/* program entry point */
int main(int argc, char *argv[]){

 FILE *fp = fopen(argv[1], "r");
 unsigned nViewers, nMovies, i, j;

 fscanf(fp, "%u %u", &nViewers, &nMovies);
 printf("%u %u\n", nViewers, nMovies);

 double * const revs = malloc(nMovies * nViewers * sizeof(double));

/*record and echo the file contents*/
 for (j = 0; j < nViewers; j ++){
  for (i = 0; i < nMovies; i++){
  fscanf(fp, "%lf", &revs[j * nMovies + i]);
  printf("%lf ", revs[j * nMovies + i]);
  }
  printf("\n");
 } 

/*record the user reviews*/
 double * const userRevs = malloc(nMovies * sizeof(double));
 printf("Enter %u movie reviews as doubles\n", nMovies - 1);

 for (i = 0; i < nMovies - 1; i++){ 
  printf("Movie #%u\n", i + 1);
  scanf("%lf", &userRevs[i]);
 }

 
/*compute and store the distances of the user and the viewers*/
 struct distance_metric * const distances = malloc(nMovies * nViewers * (sizeof(struct distance_metric)));
 for (i = 0; i < nViewers; i++){
 double sum = 0.0;
 printf("\nViewer ID    Distance\n");
 printf("-----------------------\n");
 printf("      %u\n", i);
  for (j = 0; j < nMovies - 1; j++){
   sum =  sum + fabs(userRevs[j] - revs[i + j]);
   printf("              %lf\n", fabs(userRevs[j] - revs[i + j]));
  }
  distances[i].distance = sum;
  distances[i].id = i;
 }


/*sort the distances and find the k minimum distances*/

 qsort((void*)distances, nViewers, sizeof(struct  distance_metric), sortLess);
 for (j = 0; j < nViewers; j++){
  printf("\n%u %lf", distances[j].id, distances[j].distance);
}

 printf("\nThe most similar viewer was viewer #%u and the distance calculated was %lf\n", distances[0].id, distances[0].distance);
 printf("The predicated rating for movie #%u is %lf.", nMovies, revs[distances[0].id + nMovies - 1]);

 printf("\n");
 free(revs);
 free(userRevs);
 free(distances);
 
 fclose(fp);
}
