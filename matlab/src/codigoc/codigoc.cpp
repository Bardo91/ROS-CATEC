/*
 * File: codigoc.cpp
 *
 * Real-Time Workshop code generated for Simulink model codigoc.
 *
 * Model version                        : 1.93
 * Real-Time Workshop file version      : 7.6.1  (R2010bSP1)  28-Jan-2011
 * Real-Time Workshop file generated on : Fri Jul 27 12:45:35 2012
 * TLC version                          : 7.6 (Jul 13 2010)
 * C/C++ source code generated on       : Fri Jul 27 12:45:35 2012
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "codigoc.h"
#include "codigoc_private.h"

/* Function for Embedded MATLAB: '<Root>/Embedded MATLAB Function' */
real_T codigocModelClass::codigoc_indice(const real_T lista[2000000], const
  real_T nodo[3], real_T open_cont)
{
  real_T ind;
  real_T i;
  boolean_T exitg;

  /*  Funci�n para encontrar en una lista determinada el indice del nodo que se */
  /*  est� buscando. */
  /*  */
  /*  5-Septiembre-2011 */
  /*  */
  /*  FADA-CATEC */
  /*  Manuel Garc�a Rivero */
  ind = -1.0;
  i = 1.0;
  exitg = FALSE;
  while (((uint32_T)exitg == 0U) && (i <= open_cont)) {
    if ((lista[(int32_T)i + 199999] == nodo[0]) && (lista[(int32_T)i + 399999] ==
         nodo[1]) && (lista[(int32_T)i + 599999] == nodo[2])) {
      ind = i;
      exitg = TRUE;
    } else {
      i++;
    }
  }

  return ind;
}

/* Function for Embedded MATLAB: '<Root>/Embedded MATLAB Function' */
void codigocModelClass::codigoc_min(const real_T varargin_1_data[29768], const
  int32_T *varargin_1_sizes, real_T *minval, real_T *indx)
{
  real_T mtmp;
  int32_T itmp;
  int32_T ix;
  boolean_T searchingForNonNaN;
  int32_T k;
  boolean_T guard;
  boolean_T exitg;
  mtmp = varargin_1_data[0];
  itmp = 1;
  if (*varargin_1_sizes != 1) {
    ix = 1;
    guard = FALSE;
    if (rtIsNaN(varargin_1_data[0])) {
      searchingForNonNaN = TRUE;
      k = 2;
      exitg = FALSE;
      while (((uint32_T)exitg == 0U) && (k <= *varargin_1_sizes)) {
        ix++;
        if (!rtIsNaN(varargin_1_data[ix - 1])) {
          mtmp = varargin_1_data[ix - 1];
          itmp = k;
          searchingForNonNaN = FALSE;
          exitg = TRUE;
        } else {
          k++;
        }
      }

      if (!searchingForNonNaN) {
        guard = TRUE;
      }
    } else {
      guard = TRUE;
    }

    if (guard) {
      for (k = itmp + 1; k <= *varargin_1_sizes; k++) {
        ix++;
        if (varargin_1_data[ix - 1] < mtmp) {
          mtmp = varargin_1_data[ix - 1];
          itmp = k;
        }
      }
    }
  }

  *minval = mtmp;
  *indx = (real_T)itmp;
}

/* Function for Embedded MATLAB: '<Root>/Embedded MATLAB Function' */
real_T codigocModelClass::codigoc_min_f(const real_T open[2000000], real_T
  open_cont, real_T xfin, real_T yfin, real_T hfin)
{
  real_T i_min;
  real_T k;
  real_T j;
  int32_T i;
  int32_T open_nodes_sizes;
  int32_T loop_ub;
  UNUSED_PARAMETER(hfin);
  UNUSED_PARAMETER(yfin);
  UNUSED_PARAMETER(xfin);

  /* Funci�n para determinar el nodo de la lista abierta que tienen el menor */
  /* valor de f, por lo que ser� el nodo elegido para proseguir la b�squeda */
  /* (3D) */
  /*  */
  /*  5-Septiembre-2011 */
  /*  */
  /*  FADA-CATEC */
  /*  Manuel Garc�a Rivero */
  k = 0.0;
  memset((void *)(&codigoc_B.open_nodes[0]), 0, 327448U * sizeof(real_T));

  /* En primer lugar se crea una lista con los nodos de la lista abierta e */
  /* identificamos si est� el nodo de destino */
  for (j = 1.0; j <= open_cont; j++) {
    if (open[(int32_T)j - 1] == 1.0) {
      k++;
      open_nodes_sizes = (int32_T)k - 1;
      loop_ub = (int32_T)j - 1;
      for (i = 0; i < 10; i++) {
        codigoc_B.open_nodes[open_nodes_sizes + 29768 * i] = open[200000 * i +
          loop_ub];
      }

      codigoc_B.open_nodes[open_nodes_sizes + 297680] = j;

      /* crear una lista en la que ir almacenando los nodos que est�n en la lista abierta */
    }
  }

  if (k != 0.0) {
    open_nodes_sizes = (int32_T)k;
    loop_ub = (int32_T)k - 1;
    for (i = 0; i <= loop_ub; i++) {
      codigoc_B.open_nodes_data[i] = codigoc_B.open_nodes[267912 + i];
    }

    codigoc_min(&codigoc_B.open_nodes_data[0], &open_nodes_sizes, &j, &k);

    /* extraer de la lista el nodo con el menor valor de f */
    i_min = codigoc_B.open_nodes[(int32_T)k + 297679];

    /* extraer el �ndice de la lista abierta del nodo con el menor valor de f */
  } else {
    i_min = -1.0;

    /* Si la matriz open_nodes esta vacia, quiere decir que no hay m�s nodos == fin del algoritmo */
  }

  return i_min;
}

/* Function for Embedded MATLAB: '<Root>/Embedded MATLAB Function' */
void codigocModelClass::codigoc_expansionlazy(real_T xnodo, real_T ynodo, real_T
  hnodo, real_T xfin, real_T yfin, real_T hfin, real_T gnodo, const real_T
  closed_data[600000], const int32_T closed_sizes[2], real_T nx, real_T ny,
  real_T nh, const real_T A[200000], real_T exp_nodos[182], real_T *cont)
{
  real_T nodo_vec_h;
  real_T nodo_vec_y;
  real_T nodo_vec_x;
  real_T coste;
  int32_T marca;
  int32_T k;
  int32_T j;
  int32_T loop_ub;
  int32_T s[2];
  int32_T b_k;
  boolean_T exitg;

  /*  Funci�n de la que se extraen los nodos expandidos del nodo que se est� */
  /*  trabajando, as� como los valores de g, h y f */
  /*   */
  /*  Creamos una matriz que tendr� tantas filas como nodos expandidos, y 5 */
  /*  columnas: */
  /*  1: coordenada x del nodo expandido */
  /*  2: coordenada y del nodo expandido */
  /*  3: coordenada h del nodo expandido */
  /*  4: valor acumulado del coste hasta llegar hasta este nodo: g */
  /*  5: valor del heur�stico de este nodo: h */
  /*  6: valor de la funci�n f, como suma de g y h */
  /*   */
  /*  5-Septiembre-2011 */
  /*   */
  /*  FADA-CATEC */
  /*  Manuel Garc�a Rivero */
  memset((void *)&exp_nodos[0], 0, 182U * sizeof(real_T));
  *cont = 0.0;
  for (k = -1; k < 2; k++) {
    nodo_vec_h = hnodo + (real_T)k;
    for (j = -1; j < 2; j++) {
      nodo_vec_y = ynodo + (real_T)j;
      nodo_vec_x = xnodo + -1.0;
      coste = 0.0;

      /* Bucle if para eliminar los nodos expandidos fuera del mapa */
      if ((1.0 <= nodo_vec_x) && (nodo_vec_x <= nx) && (1.0 <= nodo_vec_y) &&
          (nodo_vec_y <= ny) && (1.0 <= nodo_vec_h) && (nodo_vec_h <= nh)) {
        /* Bucle if para eliminar el nodo desde el que se esta expandiendo */
        if ((nodo_vec_x != xnodo) || (nodo_vec_y != ynodo) || (nodo_vec_h !=
             hnodo)) {
          marca = 0;

          /* Bucle for para recontar todos los nodos procesados (closed) */
          s[0] = closed_sizes[0];
          s[1] = 1;
          loop_ub = 0;
          b_k = 1;
          exitg = FALSE;
          while (((uint32_T)exitg == 0U) && (b_k <= 2)) {
            if (s[b_k - 1] == 0) {
              loop_ub = 0;
              exitg = TRUE;
            } else {
              if (s[b_k - 1] > loop_ub) {
                loop_ub = s[b_k - 1];
              }

              b_k++;
            }
          }

          for (b_k = 1; b_k <= loop_ub; b_k++) {
            /* Bucle para no tener en cuenta los nodos de la lista closed */
            if ((closed_data[b_k - 1] == nodo_vec_x) && (closed_data[(b_k - 1) +
                 closed_sizes[0]] == nodo_vec_y) && (closed_data[(b_k - 1) +
                 (closed_sizes[0] << 1)] == nodo_vec_h)) {
              marca = 1;
            }
          }

          if (j == 0) {
            if ((k == 0) && (A[(((int32_T)(ynodo + 1.0) - 1) * 100 + ((int32_T)
                   fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)(hnodo
                   + 1.0) - 1) * 10000] != 0.0) && (A[(((int32_T)(ynodo + 1.0) -
                   1) * 100 + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1))
                 + ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000] != 0.0) && (A
                 [(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)fmin
                   (nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)(hnodo +
                   1.0) - 1) * 10000] != 0.0) && (A[(((int32_T)((ynodo + 1.0) -
                    1.0) - 1) * 100 + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo +
                    1.0) - 1)) + ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000]
                 != 0.0)) {
              coste = (((A[(((int32_T)(ynodo + 1.0) - 1) * 100 + ((int32_T)fmin
                (nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)(hnodo + 1.0)
                          - 1) * 10000] + A[(((int32_T)(ynodo + 1.0) - 1) * 100
                          + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1))
                         + ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000]) + A
                        [(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)
                          fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)
                         (hnodo + 1.0) - 1) * 10000]) + A[(((int32_T)((ynodo +
                1.0) - 1.0) - 1) * 100 + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo
                          + 1.0) - 1)) + ((int32_T)((hnodo + 1.0) - 1.0) - 1) *
                       10000]) / 4.0;
            }

            if ((k != 0) && (A[(((int32_T)(ynodo + 1.0) - 1) * 100 + ((int32_T)
                   fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)fmin
                  (nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] != 0.0) && (A
                 [(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)fmin
                   (nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)fmin
                  (nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] != 0.0)) {
              coste = (A[(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)
                         fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)
                        fmin(nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] + A
                       [(((int32_T)(ynodo + 1.0) - 1) * 100 + ((int32_T)fmin
                         (nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)fmin
                        (nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000]) / 2.0;
            }
          }

          if ((k == 0) && (j != 0) && (A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo
                  + 1.0) - 1) * 100 + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo +
                  1.0) - 1)) + ((int32_T)(hnodo + 1.0) - 1) * 10000] != 0.0) &&
              (A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100 +
                  ((int32_T)fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) +
               ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000] != 0.0)) {
            coste = (A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100
                        + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) +
                     ((int32_T)(hnodo + 1.0) - 1) * 10000] + A[(((int32_T)fmin
                       (nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100 + ((int32_T)
                       fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)
                      ((hnodo + 1.0) - 1.0) - 1) * 10000]) / 2.0;
          }

          if ((j != 0) && (k != 0)) {
            coste = A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100
                       + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) +
              ((int32_T)fmin(nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000];
          }

          if (coste < 100.0) {
            (*cont)++;
            exp_nodos[(int32_T)*cont - 1] = nodo_vec_x;

            /* coordenada x del nodo k vecino del nodo que se est� expandiendo */
            exp_nodos[(int32_T)*cont + 25] = nodo_vec_y;

            /* coordenada y del nodo k vecino del nodo que se est� expandiendo */
            exp_nodos[(int32_T)*cont + 51] = nodo_vec_h;

            /* coordenada h del nodo k vecino del nodo que se est� expandiendo */
            exp_nodos[(int32_T)*cont + 77] = std::sqrt((rt_pow_snf(xnodo -
              nodo_vec_x, 2.0) + rt_pow_snf(ynodo - nodo_vec_y, 2.0)) +
              rt_pow_snf(hnodo - nodo_vec_h, 2.0)) + (gnodo + coste);

            /* valor de g hasta el nodo expandido. La matriz A indica la situaci�n de los obst�culos */
            /*  Funci�n para calcular el heur�stico, que se aproximar� como la distancia */
            /*  del nodo expandido al nodo de destino */
            /*   */
            /*  10-Noviembre-2011 */
            /*   */
            /*  FADA-CATEC */
            /*  Manuel Garc�a Rivero */
            exp_nodos[(int32_T)*cont + 103] = std::sqrt((rt_pow_snf(nodo_vec_x -
              xfin, 2.0) + rt_pow_snf(nodo_vec_y - yfin, 2.0)) + rt_pow_snf
              (nodo_vec_h - hfin, 2.0));

            /* valor del heur�stico en el nodo expandido */
            exp_nodos[(int32_T)*cont + 129] = exp_nodos[(int32_T)*cont + 77] +
              exp_nodos[(int32_T)*cont + 103];

            /* valor de f=g+h en el nodo expandido */
            exp_nodos[(int32_T)*cont + 155] = (real_T)marca;
          }
        }

        /* final del bucle if de eliminar el nodo actual */
      }

      /* final del bucle if de delimitaci�n de frontera */
      coste = 0.0;

      /* Bucle if para eliminar los nodos expandidos fuera del mapa */
      if ((1.0 <= xnodo) && (xnodo <= nx) && (1.0 <= nodo_vec_y) && (nodo_vec_y <=
           ny) && (1.0 <= nodo_vec_h) && (nodo_vec_h <= nh)) {
        /* Bucle if para eliminar el nodo desde el que se esta expandiendo */
        if ((xnodo != xnodo) || (nodo_vec_y != ynodo) || (nodo_vec_h != hnodo))
        {
          marca = 0;

          /* Bucle for para recontar todos los nodos procesados (closed) */
          s[0] = closed_sizes[0];
          s[1] = 1;
          loop_ub = 0;
          b_k = 1;
          exitg = FALSE;
          while (((uint32_T)exitg == 0U) && (b_k <= 2)) {
            if (s[b_k - 1] == 0) {
              loop_ub = 0;
              exitg = TRUE;
            } else {
              if (s[b_k - 1] > loop_ub) {
                loop_ub = s[b_k - 1];
              }

              b_k++;
            }
          }

          for (b_k = 1; b_k <= loop_ub; b_k++) {
            /* Bucle para no tener en cuenta los nodos de la lista closed */
            if ((closed_data[b_k - 1] == xnodo) && (closed_data[(b_k - 1) +
                 closed_sizes[0]] == nodo_vec_y) && (closed_data[(b_k - 1) +
                 (closed_sizes[0] << 1)] == nodo_vec_h)) {
              marca = 1;
            }
          }

          if ((j == 0) && (A[(((int32_T)(ynodo + 1.0) - 1) * 100 + ((int32_T)
                 (xnodo + 1.0) - 1)) + ((int32_T)fmin(nodo_vec_h + 1.0, hnodo +
                 1.0) - 1) * 10000] != 0.0) && (A[(((int32_T)((ynodo + 1.0) -
                  1.0) - 1) * 100 + ((int32_T)(xnodo + 1.0) - 1)) + ((int32_T)
                fmin(nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] != 0.0) && (A
               [(((int32_T)((xnodo - 1.0) + 1.0) - 1) + ((int32_T)(ynodo + 1.0)
                 - 1) * 100) + ((int32_T)fmin(nodo_vec_h + 1.0, hnodo + 1.0) - 1)
               * 10000] != 0.0) && (A[(((int32_T)((ynodo + 1.0) - 1.0) - 1) *
                100 + ((int32_T)((xnodo - 1.0) + 1.0) - 1)) + ((int32_T)fmin
                (nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] != 0.0)) {
            coste = (((A[(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)
                         (xnodo + 1.0) - 1)) + ((int32_T)fmin(nodo_vec_h + 1.0,
              hnodo + 1.0) - 1) * 10000] + A[(((int32_T)(ynodo + 1.0) - 1) * 100
                        + ((int32_T)(xnodo + 1.0) - 1)) + ((int32_T)fmin
                        (nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000]) + A
                      [(((int32_T)((xnodo - 1.0) + 1.0) - 1) + ((int32_T)(ynodo
              + 1.0) - 1) * 100) + ((int32_T)fmin(nodo_vec_h + 1.0, hnodo + 1.0)
                       - 1) * 10000]) + A[(((int32_T)((ynodo + 1.0) - 1.0) - 1) *
                      100 + ((int32_T)((xnodo - 1.0) + 1.0) - 1)) + ((int32_T)
                      fmin(nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000]) / 4.0;
          }

          if ((k == 0) && (A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1)
                              * 100 + ((int32_T)(xnodo + 1.0) - 1)) + ((int32_T)
                (hnodo + 1.0) - 1) * 10000] != 0.0) && (A[(((int32_T)fmin
                 (nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100 + ((int32_T)(xnodo +
                  1.0) - 1)) + ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000] !=
               0.0) && (A[(((int32_T)((xnodo - 1.0) + 1.0) - 1) + ((int32_T)fmin
                 (nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100) + ((int32_T)(hnodo
                 + 1.0) - 1) * 10000] != 0.0) && (A[(((int32_T)((xnodo - 1.0) +
                  1.0) - 1) + ((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1)
                * 100) + ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000] != 0.0))
          {
            coste = (((A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1) *
                          100 + ((int32_T)(xnodo + 1.0) - 1)) + ((int32_T)(hnodo
              + 1.0) - 1) * 10000] + A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo +
              1.0) - 1) * 100 + ((int32_T)(xnodo + 1.0) - 1)) + ((int32_T)
                        ((hnodo + 1.0) - 1.0) - 1) * 10000]) + A[(((int32_T)
                        ((xnodo - 1.0) + 1.0) - 1) + ((int32_T)fmin(nodo_vec_y +
              1.0, ynodo + 1.0) - 1) * 100) + ((int32_T)(hnodo + 1.0) - 1) *
                      10000]) + A[(((int32_T)((xnodo - 1.0) + 1.0) - 1) +
                      ((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100)
                     + ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000]) / 4.0;
          }

          if ((k != 0) && (j != 0) && (A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo
                  + 1.0) - 1) * 100 + ((int32_T)(xnodo + 1.0) - 1)) + ((int32_T)
                fmin(nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] != 0.0) && (A
               [(((int32_T)((xnodo + 1.0) - 1.0) - 1) + ((int32_T)fmin
                 (nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100) + ((int32_T)fmin
                (nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] != 0.0)) {
            coste = (A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100
                        + ((int32_T)(xnodo + 1.0) - 1)) + ((int32_T)fmin
                      (nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] + A
                     [(((int32_T)((xnodo + 1.0) - 1.0) - 1) + ((int32_T)fmin
                       (nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100) + ((int32_T)
                      fmin(nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000]) / 2.0;
          }

          if ((j == 0) && ((k == 0) && (A[(((int32_T)(ynodo + 1.0) - 1) * 100 +
                 ((int32_T)fmin(xnodo + 1.0, xnodo + 1.0) - 1)) + ((int32_T)
                 (hnodo + 1.0) - 1) * 10000] != 0.0) && (A[(((int32_T)(ynodo +
                   1.0) - 1) * 100 + ((int32_T)fmin(xnodo + 1.0, xnodo + 1.0) -
                  1)) + ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000] != 0.0) &&
                           (A[(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 +
                               ((int32_T)fmin(xnodo + 1.0, xnodo + 1.0) - 1)) +
                            ((int32_T)(hnodo + 1.0) - 1) * 10000] != 0.0) && (A
                [(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)fmin
                  (xnodo + 1.0, xnodo + 1.0) - 1)) + ((int32_T)((hnodo + 1.0) -
                  1.0) - 1) * 10000] != 0.0))) {
            coste = (((A[(((int32_T)(ynodo + 1.0) - 1) * 100 + ((int32_T)fmin
              (xnodo + 1.0, xnodo + 1.0) - 1)) + ((int32_T)(hnodo + 1.0) - 1) *
                       10000] + A[(((int32_T)(ynodo + 1.0) - 1) * 100 +
                        ((int32_T)fmin(xnodo + 1.0, xnodo + 1.0) - 1)) +
                       ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000]) + A
                      [(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)
                        fmin(xnodo + 1.0, xnodo + 1.0) - 1)) + ((int32_T)(hnodo
                        + 1.0) - 1) * 10000]) + A[(((int32_T)((ynodo + 1.0) -
                        1.0) - 1) * 100 + ((int32_T)fmin(xnodo + 1.0, xnodo +
                        1.0) - 1)) + ((int32_T)((hnodo + 1.0) - 1.0) - 1) *
                     10000]) / 4.0;
          }

          if (coste < 100.0) {
            (*cont)++;
            exp_nodos[(int32_T)*cont - 1] = xnodo;

            /* coordenada x del nodo k vecino del nodo que se est� expandiendo */
            exp_nodos[(int32_T)*cont + 25] = nodo_vec_y;

            /* coordenada y del nodo k vecino del nodo que se est� expandiendo */
            exp_nodos[(int32_T)*cont + 51] = nodo_vec_h;

            /* coordenada h del nodo k vecino del nodo que se est� expandiendo */
            exp_nodos[(int32_T)*cont + 77] = std::sqrt((rt_pow_snf(xnodo - xnodo,
              2.0) + rt_pow_snf(ynodo - nodo_vec_y, 2.0)) + rt_pow_snf(hnodo -
              nodo_vec_h, 2.0)) + (gnodo + coste);

            /* valor de g hasta el nodo expandido. La matriz A indica la situaci�n de los obst�culos */
            /*  Funci�n para calcular el heur�stico, que se aproximar� como la distancia */
            /*  del nodo expandido al nodo de destino */
            /*   */
            /*  10-Noviembre-2011 */
            /*   */
            /*  FADA-CATEC */
            /*  Manuel Garc�a Rivero */
            exp_nodos[(int32_T)*cont + 103] = std::sqrt((rt_pow_snf(xnodo - xfin,
              2.0) + rt_pow_snf(nodo_vec_y - yfin, 2.0)) + rt_pow_snf(nodo_vec_h
              - hfin, 2.0));

            /* valor del heur�stico en el nodo expandido */
            exp_nodos[(int32_T)*cont + 129] = exp_nodos[(int32_T)*cont + 77] +
              exp_nodos[(int32_T)*cont + 103];

            /* valor de f=g+h en el nodo expandido */
            exp_nodos[(int32_T)*cont + 155] = (real_T)marca;
          }
        }

        /* final del bucle if de eliminar el nodo actual */
      }

      /* final del bucle if de delimitaci�n de frontera */
      nodo_vec_x = xnodo + 1.0;
      coste = 0.0;

      /* Bucle if para eliminar los nodos expandidos fuera del mapa */
      if ((1.0 <= nodo_vec_x) && (nodo_vec_x <= nx) && (1.0 <= nodo_vec_y) &&
          (nodo_vec_y <= ny) && (1.0 <= nodo_vec_h) && (nodo_vec_h <= nh)) {
        /* Bucle if para eliminar el nodo desde el que se esta expandiendo */
        if ((nodo_vec_x != xnodo) || (nodo_vec_y != ynodo) || (nodo_vec_h !=
             hnodo)) {
          marca = 0;

          /* Bucle for para recontar todos los nodos procesados (closed) */
          s[0] = closed_sizes[0];
          s[1] = 1;
          loop_ub = 0;
          b_k = 1;
          exitg = FALSE;
          while (((uint32_T)exitg == 0U) && (b_k <= 2)) {
            if (s[b_k - 1] == 0) {
              loop_ub = 0;
              exitg = TRUE;
            } else {
              if (s[b_k - 1] > loop_ub) {
                loop_ub = s[b_k - 1];
              }

              b_k++;
            }
          }

          for (b_k = 1; b_k <= loop_ub; b_k++) {
            /* Bucle para no tener en cuenta los nodos de la lista closed */
            if ((closed_data[b_k - 1] == nodo_vec_x) && (closed_data[(b_k - 1) +
                 closed_sizes[0]] == nodo_vec_y) && (closed_data[(b_k - 1) +
                 (closed_sizes[0] << 1)] == nodo_vec_h)) {
              marca = 1;
            }
          }

          if (j == 0) {
            if ((k == 0) && (A[(((int32_T)(ynodo + 1.0) - 1) * 100 + ((int32_T)
                   fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)(hnodo
                   + 1.0) - 1) * 10000] != 0.0) && (A[(((int32_T)(ynodo + 1.0) -
                   1) * 100 + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1))
                 + ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000] != 0.0) && (A
                 [(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)fmin
                   (nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)(hnodo +
                   1.0) - 1) * 10000] != 0.0) && (A[(((int32_T)((ynodo + 1.0) -
                    1.0) - 1) * 100 + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo +
                    1.0) - 1)) + ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000]
                 != 0.0)) {
              coste = (((A[(((int32_T)(ynodo + 1.0) - 1) * 100 + ((int32_T)fmin
                (nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)(hnodo + 1.0)
                          - 1) * 10000] + A[(((int32_T)(ynodo + 1.0) - 1) * 100
                          + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1))
                         + ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000]) + A
                        [(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)
                          fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)
                         (hnodo + 1.0) - 1) * 10000]) + A[(((int32_T)((ynodo +
                1.0) - 1.0) - 1) * 100 + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo
                          + 1.0) - 1)) + ((int32_T)((hnodo + 1.0) - 1.0) - 1) *
                       10000]) / 4.0;
            }

            if ((k != 0) && (A[(((int32_T)(ynodo + 1.0) - 1) * 100 + ((int32_T)
                   fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)fmin
                  (nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] != 0.0) && (A
                 [(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)fmin
                   (nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)fmin
                  (nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] != 0.0)) {
              coste = (A[(((int32_T)((ynodo + 1.0) - 1.0) - 1) * 100 + ((int32_T)
                         fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)
                        fmin(nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000] + A
                       [(((int32_T)(ynodo + 1.0) - 1) * 100 + ((int32_T)fmin
                         (nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)fmin
                        (nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000]) / 2.0;
            }
          }

          if ((k == 0) && (j != 0) && (A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo
                  + 1.0) - 1) * 100 + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo +
                  1.0) - 1)) + ((int32_T)(hnodo + 1.0) - 1) * 10000] != 0.0) &&
              (A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100 +
                  ((int32_T)fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) +
               ((int32_T)((hnodo + 1.0) - 1.0) - 1) * 10000] != 0.0)) {
            coste = (A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100
                        + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) +
                     ((int32_T)(hnodo + 1.0) - 1) * 10000] + A[(((int32_T)fmin
                       (nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100 + ((int32_T)
                       fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) + ((int32_T)
                      ((hnodo + 1.0) - 1.0) - 1) * 10000]) / 2.0;
          }

          if ((j != 0) && (k != 0)) {
            coste = A[(((int32_T)fmin(nodo_vec_y + 1.0, ynodo + 1.0) - 1) * 100
                       + ((int32_T)fmin(nodo_vec_x + 1.0, xnodo + 1.0) - 1)) +
              ((int32_T)fmin(nodo_vec_h + 1.0, hnodo + 1.0) - 1) * 10000];
          }

          if (coste < 100.0) {
            (*cont)++;
            exp_nodos[(int32_T)*cont - 1] = nodo_vec_x;

            /* coordenada x del nodo k vecino del nodo que se est� expandiendo */
            exp_nodos[(int32_T)*cont + 25] = nodo_vec_y;

            /* coordenada y del nodo k vecino del nodo que se est� expandiendo */
            exp_nodos[(int32_T)*cont + 51] = nodo_vec_h;

            /* coordenada h del nodo k vecino del nodo que se est� expandiendo */
            exp_nodos[(int32_T)*cont + 77] = std::sqrt((rt_pow_snf(xnodo -
              nodo_vec_x, 2.0) + rt_pow_snf(ynodo - nodo_vec_y, 2.0)) +
              rt_pow_snf(hnodo - nodo_vec_h, 2.0)) + (gnodo + coste);

            /* valor de g hasta el nodo expandido. La matriz A indica la situaci�n de los obst�culos */
            /*  Funci�n para calcular el heur�stico, que se aproximar� como la distancia */
            /*  del nodo expandido al nodo de destino */
            /*   */
            /*  10-Noviembre-2011 */
            /*   */
            /*  FADA-CATEC */
            /*  Manuel Garc�a Rivero */
            exp_nodos[(int32_T)*cont + 103] = std::sqrt((rt_pow_snf(nodo_vec_x -
              xfin, 2.0) + rt_pow_snf(nodo_vec_y - yfin, 2.0)) + rt_pow_snf
              (nodo_vec_h - hfin, 2.0));

            /* valor del heur�stico en el nodo expandido */
            exp_nodos[(int32_T)*cont + 129] = exp_nodos[(int32_T)*cont + 77] +
              exp_nodos[(int32_T)*cont + 103];

            /* valor de f=g+h en el nodo expandido */
            exp_nodos[(int32_T)*cont + 155] = (real_T)marca;
          }
        }

        /* final del bucle if de eliminar el nodo actual */
      }

      /* final del bucle if de delimitaci�n de frontera */
      /* final del bucle for i */
    }

    /* final del bucle for j */
  }

  /* final del bucle for k */
}

/* Function for Embedded MATLAB: '<Root>/Embedded MATLAB Function' */
void codigocModelClass::codigoc_refp1_sign(real_T *x)
{
  if (rtIsNaN(*x)) {
    *x = (rtNaN);
  } else if (*x > 0.0) {
    *x = 1.0;
  } else if (*x < 0.0) {
    *x = -1.0;
  } else {
    *x = 0.0;
  }
}

/* Function for Embedded MATLAB: '<Root>/Embedded MATLAB Function' */
real_T codigocModelClass::codigoc_lineofsight3D(const real_T node[3], const
  real_T parent[3], const real_T A[200000])
{
  real_T los;
  real_T lambda[83];
  real_T x[83];
  real_T y[83];
  real_T k;
  real_T c;
  real_T c_0;
  real_T c_1;
  real_T c_2;
  real_T b_x[101];
  real_T b_y[101];
  real_T z[101];
  real_T c_x;
  real_T g;
  int32_T i;
  real_T v_idx;
  real_T v_idx_0;
  real_T v_idx_1;
  int8_T vv_idx;
  int8_T vv_idx_0;
  int8_T vv_idx_1;
  static real_T tmp[101] = { 0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08,
    0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.2, 0.21,
    0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.3, 0.31, 0.32, 0.33, 0.34,
    0.35000000000000003, 0.36, 0.37, 0.38, 0.39, 0.4, 0.41000000000000003, 0.42,
    0.43, 0.44, 0.45, 0.46, 0.47000000000000003, 0.48, 0.49, 0.5, 0.51, 0.52,
    0.53, 0.54, 0.55, 0.56, 0.57000000000000006, 0.58000000000000007, 0.59, 0.6,
    0.61, 0.62, 0.63, 0.64, 0.64999999999999991, 0.65999999999999992,
    0.66999999999999993, 0.67999999999999994, 0.69, 0.7, 0.71, 0.72, 0.73, 0.74,
    0.75, 0.76, 0.77, 0.78, 0.79, 0.8, 0.81, 0.82000000000000006, 0.83, 0.84,
    0.85, 0.86, 0.87, 0.88, 0.89, 0.9, 0.91, 0.92, 0.92999999999999994, 0.94,
    0.95, 0.96, 0.97, 0.98, 0.99, 1.0 };

  static real_T tmp_0[82] = { 0.0, 0.0123, 0.0246, 0.0369, 0.0492, 0.0615,
    0.0738, 0.0861, 0.0984, 0.1107, 0.123, 0.1353, 0.1476, 0.15990000000000001,
    0.1722, 0.1845, 0.1968, 0.2091, 0.2214, 0.2337, 0.246, 0.25830000000000003,
    0.2706, 0.2829, 0.2952, 0.3075, 0.31980000000000003, 0.3321, 0.3444, 0.3567,
    0.369, 0.38130000000000003, 0.3936, 0.4059, 0.4182, 0.4305, 0.4428, 0.4551,
    0.4674, 0.4797, 0.492, 0.5043, 0.5166, 0.52889999999999993,
    0.5411999999999999, 0.55349999999999988, 0.5658, 0.5781, 0.5904, 0.6027,
    0.615, 0.6273, 0.6396, 0.65189999999999992, 0.6641999999999999,
    0.67649999999999988, 0.6888, 0.7011, 0.7134, 0.7257, 0.738, 0.7503, 0.7626,
    0.77489999999999992, 0.7871999999999999, 0.7995, 0.8118, 0.82409999999999994,
    0.83639999999999992, 0.8487, 0.861, 0.8733, 0.88559999999999994,
    0.89789999999999992, 0.9102, 0.9225, 0.9348, 0.94709999999999994,
    0.95939999999999992, 0.9717, 0.984, 0.9963 };

  /*  Funci�n para determinar si el nodo snodo tiene linea de vista con el nodo */
  /*  sparent, que es uno de los padres de snodo. Si tiene l�nea de vista ==> */
  /*  los=1, si no la tiene ==> los=0. */
  /*  */
  /*  5-Septiembre-2011 */
  /*  */
  /*  FADA-CATEC */
  /*  Manuel Garc�a Rivero */
  memset((void *)&lambda[0], 0, 83U * sizeof(real_T));

  /* 0.011234; %distancia de discretizaci�n en funci�n de la distancia */
  for (i = 0; i < 82; i++) {
    lambda[i] = tmp_0[i];
  }

  lambda[82] = 1.0;
  los = 1.0;

  /* caso 1 ==> recta en el espacio */
  if ((node[0] != parent[0]) && (node[1] != parent[1]) && (node[2] != parent[2]))
  {
    v_idx = node[0] - parent[0];
    v_idx_0 = node[1] - parent[1];
    v_idx_1 = node[2] - parent[2];
    for (i = 0; i < 83; i++) {
      x[i] = v_idx * lambda[i] + parent[0];
      y[i] = v_idx_0 * lambda[i] + parent[1];
      lambda[i] = v_idx_1 * lambda[i] + parent[2];
    }

    for (i = 0; i < 81; i++) {
      if (((std::floor(x[i + 1]) - std::floor(x[i]) != 0.0) || (std::floor(y[i +
             1]) - std::floor(y[i]) != 0.0) || (std::floor(lambda[i + 1]) - std::
            floor(lambda[i]) != 0.0)) && (A[(((int32_T)(std::floor(y[i + 1]) +
              1.0) - 1) * 100 + ((int32_T)(std::floor(x[i + 1]) + 1.0) - 1)) +
           ((int32_T)(std::floor(lambda[i + 1]) + 1.0) - 1) * 10000] != 0.0)) {
        los = 0.0;
      }
    }
  }

  /* caso 2 ==> recta contenida en un plano de la discretizaci�n */
  if (((node[0] != parent[0]) && (node[1] != parent[1]) && (node[2] == parent[2]))
      || ((node[0] != parent[0]) && (node[1] == parent[1]) && (node[2] !=
        parent[2])) || ((node[0] == parent[0]) && (node[1] != parent[1]) &&
                        (node[2] != parent[2]))) {
    v_idx_1 = node[0] - parent[0];
    vv_idx = (v_idx_1 == 0.0);
    v_idx = v_idx_1;
    v_idx_1 = node[1] - parent[1];
    vv_idx_0 = (v_idx_1 == 0.0);
    v_idx_0 = v_idx_1;
    v_idx_1 = node[2] - parent[2];
    vv_idx_1 = (v_idx_1 == 0.0);

    /* distancia de discretizaci�n en funci�n de la distancia */
    for (i = 0; i < 101; i++) {
      b_x[i] = v_idx * tmp[i] + parent[0];
      b_y[i] = v_idx_0 * tmp[i] + parent[1];
      z[i] = v_idx_1 * tmp[i] + parent[2];
    }

    for (i = 2; i < 101; i++) {
      if ((A[(((int32_T)(std::floor(b_y[i - 1]) + 1.0) - 1) * 100 + ((int32_T)
             (std::floor(b_x[i - 1]) + 1.0) - 1)) + ((int32_T)(std::floor(z[i -
              1]) + 1.0) - 1) * 10000] != 0.0) && (A[(((int32_T)((std::floor
               (b_y[i - 1]) - (real_T)vv_idx_0) + 1.0) - 1) * 100 + ((int32_T)
             ((std::floor(b_x[i - 1]) - (real_T)vv_idx) + 1.0) - 1)) + ((int32_T)
            ((std::floor(z[i - 1]) - (real_T)vv_idx_1) + 1.0) - 1) * 10000] !=
           0.0)) {
        los = 0.0;
      }
    }
  }

  /* caso 3 ==> recta contenida en una arista de la discretizaci�n */
  if (((node[0] != parent[0]) && (node[1] == parent[1]) && (node[2] == parent[2]))
      || ((node[0] == parent[0]) && (node[1] != parent[1]) && (node[2] ==
        parent[2])) || ((node[0] == parent[0]) && (node[1] == parent[1]) &&
                        (node[2] != parent[2]))) {
    v_idx = node[0] - parent[0];
    v_idx_0 = node[1] - parent[1];
    v_idx_1 = node[2] - parent[2];
    if (v_idx != 0.0) {
      /* arista en la direcci�n de x */
      c_x = v_idx;
      codigoc_refp1_sign(&c_x);
      c_x += parent[0];
      k = 1.0;
      while (k <= std::abs(v_idx)) {
        c = A[(((int32_T)(node[1] + 1.0) - 1) * 100 + ((int32_T)(c_x + 1.0) - 1))
          + ((int32_T)(node[2] + 1.0) - 1) * 10000];
        c_0 = A[(((int32_T)((node[1] + 1.0) - 1.0) - 1) * 100 + ((int32_T)(c_x +
                   1.0) - 1)) + ((int32_T)(node[2] + 1.0) - 1) * 10000];
        c_1 = A[(((int32_T)((node[1] + 1.0) - 1.0) - 1) * 100 + ((int32_T)(c_x +
                   1.0) - 1)) + ((int32_T)((node[2] + 1.0) - 1.0) - 1) * 10000];
        c_2 = A[(((int32_T)(node[1] + 1.0) - 1) * 100 + ((int32_T)(c_x + 1.0) -
                  1)) + ((int32_T)((node[2] + 1.0) - 1.0) - 1) * 10000];
        k++;
        g = v_idx;
        codigoc_refp1_sign(&g);
        c_x += g;
        if ((c != 0.0) && (c_0 != 0.0) && (c_1 != 0.0) && (c_2 != 0.0)) {
          los = 0.0;
        }
      }
    }

    if (v_idx_0 != 0.0) {
      /* arista en la direcci�n de y */
      c_x = v_idx_0;
      codigoc_refp1_sign(&c_x);
      c_x += parent[1];
      k = 1.0;
      while (k <= std::abs(v_idx_0)) {
        c = A[(((int32_T)(c_x + 1.0) - 1) * 100 + ((int32_T)(node[0] + 1.0) - 1))
          + ((int32_T)(node[2] + 1.0) - 1) * 10000];
        c_0 = A[(((int32_T)((node[0] + 1.0) - 1.0) - 1) + ((int32_T)(c_x + 1.0)
                  - 1) * 100) + ((int32_T)(node[2] + 1.0) - 1) * 10000];
        c_1 = A[(((int32_T)((node[0] + 1.0) - 1.0) - 1) + ((int32_T)(c_x + 1.0)
                  - 1) * 100) + ((int32_T)((node[2] + 1.0) - 1.0) - 1) * 10000];
        c_2 = A[(((int32_T)(c_x + 1.0) - 1) * 100 + ((int32_T)(node[0] + 1.0) -
                  1)) + ((int32_T)((node[2] + 1.0) - 1.0) - 1) * 10000];
        k++;
        g = v_idx_0;
        codigoc_refp1_sign(&g);
        c_x += g;
        if ((c != 0.0) && (c_0 != 0.0) && (c_1 != 0.0) && (c_2 != 0.0)) {
          los = 0.0;
        }
      }
    }

    if (v_idx_1 != 0.0) {
      /* arista en la direcci�n de z */
      c_x = v_idx_1;
      codigoc_refp1_sign(&c_x);
      c_x += parent[2];
      k = 1.0;
      while (k <= std::abs(v_idx_1)) {
        c = A[(((int32_T)(node[1] + 1.0) - 1) * 100 + ((int32_T)(node[0] + 1.0)
                - 1)) + ((int32_T)(c_x + 1.0) - 1) * 10000];
        c_0 = A[(((int32_T)((node[0] + 1.0) - 1.0) - 1) + ((int32_T)(node[1] +
                   1.0) - 1) * 100) + ((int32_T)(c_x + 1.0) - 1) * 10000];
        c_1 = A[(((int32_T)((node[1] + 1.0) - 1.0) - 1) * 100 + ((int32_T)
                  ((node[0] + 1.0) - 1.0) - 1)) + ((int32_T)(c_x + 1.0) - 1) *
          10000];
        c_2 = A[(((int32_T)((node[1] + 1.0) - 1.0) - 1) * 100 + ((int32_T)(node
                   [0] + 1.0) - 1)) + ((int32_T)(c_x + 1.0) - 1) * 10000];
        k++;
        g = v_idx_1;
        codigoc_refp1_sign(&g);
        c_x += g;
        if ((c != 0.0) && (c_0 != 0.0) && (c_1 != 0.0) && (c_2 != 0.0)) {
          los = 0.0;
        }
      }
    }
  }

  return los;
}

/* Model step function */
void codigocModelClass::step()
{
  real_T nx;
  real_T ny;
  real_T nh;
  real_T xini;
  real_T yini;
  real_T hini;
  real_T xfin;
  real_T yfin;
  real_T hfin;
  real_T open_cont;
  real_T closed_cont;
  real_T nodo[3];
  real_T heurstart;
  int32_T NoSol;
  real_T iter;
  real_T k;
  real_T i;
  real_T ind_parent;
  real_T nodopadre[3];
  real_T nodos_exp[182];
  real_T cont;
  int32_T b;
  boolean_T exitg;
  real_T closed[3];
  real_T open[3];
  real_T open_0[3];
  real_T nodos_exp_0[3];
  int32_T i_0;
  int32_T k_0;
  real_T openlazy_data[156];
  int32_T closed_sizes[2];
  real_T nodos_exp_data[182];
  int32_T trayecTHETALstaresc_sizes_idx;
  int32_T openlazy_sizes_idx;
  real_T ext0_idx;
  real_T ext0_idx_0;
  real_T ext0_idx_1;
  real_T ext1_idx;
  real_T ext1_idx_0;
  real_T ext1_idx_1;
  int32_T loop_ub;

  /* Embedded MATLAB: '<Root>/Embedded MATLAB Function' incorporates:
   *  Inport: '<Root>/A'
   *  Inport: '<Root>/lismespacio'
   *  Inport: '<Root>/n'
   *  Inport: '<Root>/wpfin'
   *  Inport: '<Root>/wpini'
   */
  /* Embedded MATLAB Function 'Embedded MATLAB Function': '<S1>:1' */
  /*  Algoritmo THETA* planteado en nodos para la planificaci�n de trayectorias */
  /*  de aeronaves en presencia de n�cleos meteorol�gicos de cierto riesgo (3D) */
  /*  La b�squeda se realiza asumiendo que el nodo t�nea l�nea de vista y  */
  /*  posteriormente se comprueba si tiene o no, y si no tiene se desecha y se  */
  /*  busca otro. Riesgo generado a partir de una matriz creada A. */
  /*  */
  /*  14-Octubre-2011 */
  /*  */
  /*  FADA-CATEC */
  /*  Manuel Garc�a Rivero */
  /*  A : Matriz obst�culos */
  /*  limsespacio:  */
  /*  wpini: origen */
  /*  wpfin: destino */
  /*  n: n�mero de puntos de la discretizaci�n en cada eje */
  /* %%%%%%%%%%%%% */
  /* % ENTRADAS %% */
  /* %%%%%%%%%%%%% */
  /* '<S1>:1:29' */
  /* '<S1>:1:30' */
  /* '<S1>:1:31' */
  /*  Datos de actuaciones de la aeronave para la discretizaci�n en altura */
  /*  V=15; %velocidad de vuelo */
  /*  RC=2; %rate of climb, velocidad de ascenso */
  /*  gamma=asin(RC/V); %�ngulo de ascenso   */
  /* %%%%%%%%%%%%%%%%%%% */
  /* % DISCRETIZACI�N %% */
  /* %%%%%%%%%%%%%%%%%%% */
  /* '<S1>:1:44' */
  nx = codigoc_U.n[0];

  /* '<S1>:1:44' */
  ny = codigoc_U.n[1];

  /* n�mero de puntos de la discretizaci�n en cada eje */
  /* '<S1>:1:45' */
  nh = codigoc_U.n[2];

  /* n�mero de puntos de la discretizaci�n en altura */
  /* n�mero total de puntos de la discretizaci�n en el plano */
  /* '<S1>:1:47' */
  ext0_idx = codigoc_U.limsespacio[0];
  ext0_idx_0 = codigoc_U.limsespacio[2];
  ext0_idx_1 = codigoc_U.limsespacio[4];

  /* '<S1>:1:47' */
  ext1_idx = codigoc_U.limsespacio[1];
  ext1_idx_0 = codigoc_U.limsespacio[3];
  ext1_idx_1 = codigoc_U.limsespacio[5];

  /*   */
  /*  dx=(x1-x0)/(n(1)-1); dy=(y1-y0)/(n(2)-1); dh=(h1-h0)/(n(3)-1); %paso de la discretizaci�n en cada eje */
  /*  discret=[dx dy dh];  */
  /*   */
  /*  %%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  %% MAPAS METEOROL�GICOS %% */
  /*  %%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*   */
  /*  %Se mete el mapa meteorol�gico a trav�s de cubos que representan regiones */
  /*  %del espacio en las que puede existir un riesgo */
  /*  %A tiene 7 niveles de celda: cada 200m hasta 1400m, empezando desde 0. */
  /*  niveles=(h1-h0)/dh; %7 */
  /*  color=[0 1 0; 1 1 0; 1 0 0]; ncolor=size(color,1); */
  /*  regiones=2; %se pondr�n dos regiones de riesgo como m�ximo */
  /*  lims=zeros(7,6,3,1);  */
  /* REGIONES DE RIESGO */
  /* REGION1 */
  /* %Zona verde */
  /*  lims(:,:,1,1)=[zeros(1,6);  */
  /*      20000 30000 0 45000 800 900;...  */
  /*      20000 30000 0 45000 900 1000;...  */
  /*      20000 30000 0 45000 1000 1100;... */
  /*      20000 30000 0 45000 1100 1200;... */
  /*      20000 30000 0 45000 1200 1300;... */
  /*      zeros(1,6)]; */
  /* A=crearmatriz(limsespacio,discret,lims); */
  /* A=zeros(100, 100, 20); */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* % ORIGEN Y DESTINO DE LA AERONAVE EN LA DISCRETIZACI�N %% */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* Origen */
  /* '<S1>:1:84' */
  /* '<S1>:1:85' */
  /* '<S1>:1:86' */
  /* '<S1>:1:87' */
  xini = std::floor(((codigoc_U.n[0] - 1.0) * codigoc_U.wpini[0] +
                     (codigoc_U.limsespacio[1] - codigoc_U.n[0] *
                      codigoc_U.limsespacio[0])) / (codigoc_U.limsespacio[1] -
    codigoc_U.limsespacio[0]));

  /* '<S1>:1:87' */
  yini = std::floor(((codigoc_U.n[1] - 1.0) * codigoc_U.wpini[1] +
                     (codigoc_U.limsespacio[3] - codigoc_U.n[1] *
                      codigoc_U.limsespacio[2])) / (codigoc_U.limsespacio[3] -
    codigoc_U.limsespacio[2]));

  /* '<S1>:1:87' */
  hini = std::floor(((codigoc_U.n[2] - 1.0) * codigoc_U.wpini[2] +
                     (codigoc_U.limsespacio[5] - codigoc_U.n[2] *
                      codigoc_U.limsespacio[4])) / (codigoc_U.limsespacio[5] -
    codigoc_U.limsespacio[4]));

  /* Destino */
  /* '<S1>:1:90' */
  /* '<S1>:1:91' */
  /* '<S1>:1:92' */
  /* '<S1>:1:93' */
  xfin = std::floor(((codigoc_U.n[0] - 1.0) * codigoc_U.wpfin[0] +
                     (codigoc_U.limsespacio[1] - codigoc_U.n[0] *
                      codigoc_U.limsespacio[0])) / (codigoc_U.limsespacio[1] -
    codigoc_U.limsespacio[0]));

  /* '<S1>:1:93' */
  yfin = std::floor(((codigoc_U.n[1] - 1.0) * codigoc_U.wpfin[1] +
                     (codigoc_U.limsespacio[3] - codigoc_U.n[1] *
                      codigoc_U.limsespacio[2])) / (codigoc_U.limsespacio[3] -
    codigoc_U.limsespacio[2]));

  /* '<S1>:1:93' */
  hfin = std::floor(((codigoc_U.n[2] - 1.0) * codigoc_U.wpfin[2] +
                     (codigoc_U.limsespacio[5] - codigoc_U.n[2] *
                      codigoc_U.limsespacio[4])) / (codigoc_U.limsespacio[5] -
    codigoc_U.limsespacio[4]));

  /* %%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* % ALGORITMO LAZY THETA* %% */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* Definici�n de las listas abiertas y cerradas */
  /* LISTA ABIERTA */
  /* [id (1 si el nodo pertenece a la lista � 0 si ya no pertenece), xnodo, ynodo, hnodo, xpadre, ypadre, hpadre, g, h, f] */
  /* '<S1>:1:104' */
  memset((void *)(&codigoc_B.open[0]), 0, 2000000U * sizeof(real_T));

  /* definicion de la lista abierta, preallocating para ahorrar tiempo */
  /* LISTA CERRADA */
  /* [xnodo ynodo] */
  /* '<S1>:1:108' */
  memset((void *)(&codigoc_B.closed[0]), 0, 600000U * sizeof(real_T));

  /* definicion de la lista cerrada, preallocating para ahorrar tiempo */
  /* Contadores de las listas abierta y cerrada */
  /* contador de los nodos de la lista abierta */
  /* '<S1>:1:112' */
  closed_cont = 0.0;

  /* contador de los nodos de la lista cerrada */
  /* Inicio del algoritmo ==> empezamos analizando el nodo del origen */
  /* '<S1>:1:115' */
  nodo[0] = xini;
  nodo[1] = yini;
  nodo[2] = hini;

  /* no hay coste de llegar del nodo inicial a el mismo, es decir que el padre del nodo inicial es el mismo */
  /* '<S1>:1:117' */
  nodopadre[0] = xini;
  nodopadre[1] = yini;
  nodopadre[2] = hini;

  /*  Funci�n para calcular el heur�stico, que se aproximar� como la distancia */
  /*  del nodo expandido al nodo de destino */
  /*   */
  /*  10-Noviembre-2011 */
  /*   */
  /*  FADA-CATEC */
  /*  Manuel Garc�a Rivero */
  heurstart = std::sqrt((rt_pow_snf(nodopadre[0] - xfin, 2.0) + rt_pow_snf
    (nodopadre[1] - yfin, 2.0)) + rt_pow_snf(nodopadre[2] - hfin, 2.0));

  /* heur�stico del nodo inicial, distancia al nodo final */
  /* '<S1>:1:118' */
  /* funci�n f como suma de g y el heuristico */
  /* Metemos el nodo origen en la lista abierta */
  /* '<S1>:1:121' */
  open_cont = 1.0;

  /* '<S1>:1:122' */
  codigoc_B.open[0] = 1.0;
  codigoc_B.open[200000] = xini;
  codigoc_B.open[400000] = yini;
  codigoc_B.open[600000] = hini;
  codigoc_B.open[800000] = xini;
  codigoc_B.open[1000000] = yini;
  codigoc_B.open[1200000] = hini;
  codigoc_B.open[1400000] = 0.0;
  codigoc_B.open[1600000] = heurstart;
  codigoc_B.open[1800000] = heurstart;

  /* metemos en la lista abierta nodo origen, se�alando que el es su propio padre */
  /* '<S1>:1:124' */
  NoSol = 0;

  /* par�metro para identificar que hay soluci�n, si NoSol=1 quiere decir que no habr� trayectoria */
  /* '<S1>:1:126' */
  iter = 0.0;

  /* numero de iteraciones necesarias para llegar al nodo final  */
  /* time=cputime; */
  exitg = FALSE;
  while (((uint32_T)exitg == 0U) && ((nodo[0] != xfin) || (nodo[1] != yfin) ||
          (nodo[2] != hfin))) {
    /* '<S1>:1:132' */
    /* Encontrar el nodo de la lista abierta que tenga el menor valor de f */
    /* '<S1>:1:135' */
    i = codigoc_min_f(&codigoc_B.open[0], open_cont, xfin, yfin, hfin);
    if (i != -1.0) {
      /* '<S1>:1:137' */
      /* Establecer el nodo sucesor como el que tiene menor valor de f */
      /* '<S1>:1:139' */
      i_0 = (int32_T)i - 1;
      nodo[0] = codigoc_B.open[i_0 + 200000];
      nodo[1] = codigoc_B.open[i_0 + 400000];
      nodo[2] = codigoc_B.open[i_0 + 600000];

      /* Actualizar el valor del coste del camino hasta llegar al nodo */
      /* '<S1>:1:142' */
      k = codigoc_B.open[(int32_T)i + 1399999];

      /* Movemos el nodo a la lista cerrada */
      /* '<S1>:1:145' */
      closed_cont++;

      /* '<S1>:1:146' */
      trayecTHETALstaresc_sizes_idx = (int32_T)closed_cont - 1;
      i_0 = (int32_T)i - 1;
      codigoc_B.closed[trayecTHETALstaresc_sizes_idx] = codigoc_B.open[i_0 +
        200000];
      codigoc_B.closed[trayecTHETALstaresc_sizes_idx + 200000] =
        codigoc_B.open[i_0 + 400000];
      codigoc_B.closed[trayecTHETALstaresc_sizes_idx + 400000] =
        codigoc_B.open[i_0 + 600000];

      /* Quitamos el nodo de la lista abierta */
      /* '<S1>:1:149' */
      codigoc_B.open[(int32_T)i - 1] = 0.0;

      /* Expandimos la b�squeda a partir del nodo elegido */
      closed_sizes[0] = (int32_T)closed_cont;
      closed_sizes[1] = 3;
      loop_ub = (int32_T)closed_cont - 1;
      for (i_0 = 0; i_0 <= loop_ub; i_0++) {
        codigoc_B.closed_data[i_0] = codigoc_B.closed[i_0];
      }

      loop_ub = (int32_T)closed_cont - 1;
      for (i_0 = 0; i_0 <= loop_ub; i_0++) {
        codigoc_B.closed_data[i_0 + closed_sizes[0]] = codigoc_B.closed[i_0 +
          200000];
      }

      loop_ub = (int32_T)closed_cont - 1;
      for (i_0 = 0; i_0 <= loop_ub; i_0++) {
        codigoc_B.closed_data[i_0 + (closed_sizes[0] << 1)] =
          codigoc_B.closed[i_0 + 400000];
      }

      codigoc_expansionlazy(nodo[0], nodo[1], nodo[2], xfin, yfin, hfin, k,
                            &codigoc_B.closed_data[0], closed_sizes, nx, ny, nh,
                            &codigoc_U.A[0], nodos_exp, &cont);
      if (1.0 > cont) {
        b = 0;
      } else {
        b = (int32_T)cont;
      }

      /* '<S1>:1:161' */
      /* '<S1>:1:163' */
      i_0 = (int32_T)i - 1;
      open_0[0] = codigoc_B.open[i_0 + 800000];
      open_0[1] = codigoc_B.open[i_0 + 1000000];
      open_0[2] = codigoc_B.open[i_0 + 1200000];
      if (codigoc_lineofsight3D(nodo, open_0, &codigoc_U.A[0]) != 1.0) {
        /* '<S1>:1:165' */
        /* '<S1>:1:167' */
        k = 0.0;

        /* '<S1>:1:168' */
        openlazy_sizes_idx = (int32_T)cont;
        loop_ub = (int32_T)cont * 6 - 1;
        for (i_0 = 0; i_0 <= loop_ub; i_0++) {
          openlazy_data[i_0] = 0.0;
        }

        for (ind_parent = 1.0; ind_parent <= cont; ind_parent++) {
          /* '<S1>:1:170' */
          if (nodos_exp[(int32_T)ind_parent + 155] == 1.0) {
            /* '<S1>:1:172' */
            /* '<S1>:1:173' */
            /* '<S1>:1:174' */
            k++;

            /* '<S1>:1:175' */
            k_0 = (int32_T)k - 1;
            for (i_0 = 0; i_0 < 7; i_0++) {
              loop_ub = b - 1;
              for (trayecTHETALstaresc_sizes_idx = 0;
                   trayecTHETALstaresc_sizes_idx <= loop_ub;
                   trayecTHETALstaresc_sizes_idx++) {
                nodos_exp_data[trayecTHETALstaresc_sizes_idx + b * i_0] =
                  nodos_exp[26 * i_0 + trayecTHETALstaresc_sizes_idx];
              }
            }

            trayecTHETALstaresc_sizes_idx = (int32_T)ind_parent - 1;
            openlazy_data[k_0] = nodos_exp_data[trayecTHETALstaresc_sizes_idx];
            openlazy_data[k_0 + openlazy_sizes_idx] =
              nodos_exp_data[trayecTHETALstaresc_sizes_idx + b];
            openlazy_data[k_0 + (openlazy_sizes_idx << 1)] = nodos_exp_data[(b <<
              1) + trayecTHETALstaresc_sizes_idx];

            /* '<S1>:1:176' */
            for (i_0 = 0; i_0 < 7; i_0++) {
              loop_ub = b - 1;
              for (trayecTHETALstaresc_sizes_idx = 0;
                   trayecTHETALstaresc_sizes_idx <= loop_ub;
                   trayecTHETALstaresc_sizes_idx++) {
                nodos_exp_data[trayecTHETALstaresc_sizes_idx + b * i_0] =
                  nodos_exp[26 * i_0 + trayecTHETALstaresc_sizes_idx];
              }
            }

            trayecTHETALstaresc_sizes_idx = (int32_T)ind_parent - 1;
            nodos_exp_0[0] = nodos_exp_data[trayecTHETALstaresc_sizes_idx];
            nodos_exp_0[1] = nodos_exp_data[trayecTHETALstaresc_sizes_idx + b];
            nodos_exp_0[2] = nodos_exp_data[(b << 1) +
              trayecTHETALstaresc_sizes_idx];
            k_0 = (int32_T)k - 1;
            trayecTHETALstaresc_sizes_idx = (int32_T)codigoc_indice
              (&codigoc_B.open[0], nodos_exp_0, open_cont) - 1;
            openlazy_data[k_0 + openlazy_sizes_idx * 3] =
              codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1400000];
            openlazy_data[k_0 + (openlazy_sizes_idx << 2)] =
              codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1600000];
            openlazy_data[k_0 + openlazy_sizes_idx * 5] =
              codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1800000];
          }
        }

        if (1.0 > k) {
          trayecTHETALstaresc_sizes_idx = 0;
        } else {
          trayecTHETALstaresc_sizes_idx = (int32_T)k;
        }

        loop_ub = trayecTHETALstaresc_sizes_idx - 1;
        for (i_0 = 0; i_0 <= loop_ub; i_0++) {
          codigoc_B.openlazy_data[i_0] = openlazy_data[openlazy_sizes_idx * 5 +
            i_0];
        }

        codigoc_min(&codigoc_B.openlazy_data[0], &trayecTHETALstaresc_sizes_idx,
                    &ind_parent, &heurstart);

        /* '<S1>:1:182' */
        i_0 = (int32_T)i - 1;
        loop_ub = (int32_T)heurstart - 1;
        codigoc_B.open[i_0 + 800000] = openlazy_data[loop_ub];
        codigoc_B.open[i_0 + 1000000] = openlazy_data[loop_ub +
          openlazy_sizes_idx];
        codigoc_B.open[i_0 + 1200000] = openlazy_data[(openlazy_sizes_idx << 1)
          + loop_ub];

        /* '<S1>:1:183' */
        /*  Funci�n para calcular el heur�stico, que se aproximar� como la distancia */
        /*  del nodo expandido al nodo de destino */
        /*   */
        /*  10-Noviembre-2011 */
        /*   */
        /*  FADA-CATEC */
        /*  Manuel Garc�a Rivero */
        codigoc_B.open[(int32_T)i + 1399999] = std::sqrt((rt_pow_snf(nodo[1] -
          openlazy_data[((int32_T)heurstart - 1) + openlazy_sizes_idx], 2.0) +
          rt_pow_snf(nodo[0] - openlazy_data[(int32_T)heurstart - 1], 2.0)) +
          rt_pow_snf(nodo[2] - openlazy_data[((int32_T)heurstart - 1) +
                     (openlazy_sizes_idx << 1)], 2.0)) + openlazy_data[((int32_T)
          heurstart - 1) + openlazy_sizes_idx * 3];

        /* '<S1>:1:184' */
        /*  Funci�n para calcular el heur�stico, que se aproximar� como la distancia */
        /*  del nodo expandido al nodo de destino */
        /*   */
        /*  10-Noviembre-2011 */
        /*   */
        /*  FADA-CATEC */
        /*  Manuel Garc�a Rivero */
        codigoc_B.open[(int32_T)i + 1799999] = std::sqrt((rt_pow_snf(nodo[0] -
          xfin, 2.0) + rt_pow_snf(nodo[1] - yfin, 2.0)) + rt_pow_snf(nodo[2] -
          hfin, 2.0)) + codigoc_B.open[(int32_T)i + 1399999];
      }

      /* Comprobamos que el nodo expandido no est� contenido en la lista */
      /* abierta, y si est� contenido y presenta un camino menos costoso (menor */
      /* f), actualizamos la lista */
      /* '<S1>:1:192' */
      i_0 = (int32_T)i - 1;

      /* '<S1>:1:193' */
      trayecTHETALstaresc_sizes_idx = (int32_T)i - 1;
      nodopadre[0] = codigoc_B.open[i_0 + 800000];
      open[0] = codigoc_B.open[trayecTHETALstaresc_sizes_idx + 800000];
      nodopadre[1] = codigoc_B.open[i_0 + 1000000];
      open[1] = codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1000000];
      nodopadre[2] = codigoc_B.open[i_0 + 1200000];
      open[2] = codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1200000];
      ind_parent = codigoc_indice(&codigoc_B.open[0], open, open_cont);
      for (heurstart = 1.0; heurstart <= cont; heurstart++) {
        /* '<S1>:1:195' */
        if (nodos_exp[(int32_T)heurstart + 155] == 0.0) {
          /* '<S1>:1:197' */
          /* '<S1>:1:200' */
          trayecTHETALstaresc_sizes_idx = 0;

          /* '<S1>:1:201' */
          /* '<S1>:1:202' */
          i = std::sqrt((rt_pow_snf(nodopadre[1] - nodos_exp[(int32_T)heurstart
            + 25], 2.0) + rt_pow_snf(nodopadre[0] - nodos_exp[(int32_T)heurstart
            - 1], 2.0)) + rt_pow_snf(nodopadre[2] - nodos_exp[(int32_T)heurstart
            + 51], 2.0)) + codigoc_B.open[(int32_T)ind_parent + 1399999];

          /* PATH2 */
          for (k = 1.0; k <= open_cont; k++) {
            /* '<S1>:1:205' */
            if ((nodos_exp[(int32_T)heurstart - 1] == codigoc_B.open[(int32_T)k
                 + 199999]) && (nodos_exp[(int32_T)heurstart + 25] ==
                                codigoc_B.open[(int32_T)k + 399999]) &&
                (nodos_exp[(int32_T)heurstart + 51] == codigoc_B.open[(int32_T)k
                 + 599999])) {
              /* '<S1>:1:207' */
              /* si el nodo expandido estaba contenido en la lista abierta */
              /* '<S1>:1:208' */
              codigoc_B.open[(int32_T)k + 1399999] = fmin(codigoc_B.open
                [(int32_T)k + 1399999], i);
              if (codigoc_B.open[(int32_T)k + 1399999] == i) {
                /* '<S1>:1:210' */
                /* si el nodo expandido que ya estaba en la lista abierta tiene un valor de f menor en esta nueva expansion, se actualiza... */
                /* Se actualizan: padre, g y h (f ya estaba actualizado) */
                /* '<S1>:1:212' */
                k_0 = (int32_T)k - 1;
                codigoc_B.open[k_0 + 800000] = nodopadre[0];
                codigoc_B.open[k_0 + 1000000] = nodopadre[1];
                codigoc_B.open[k_0 + 1200000] = nodopadre[2];

                /* '<S1>:1:213' */
                codigoc_B.open[(int32_T)k + 1599999] = nodos_exp[(int32_T)
                  heurstart + 103];

                /* '<S1>:1:214' */
                codigoc_B.open[(int32_T)k + 1799999] = nodos_exp[(int32_T)
                  heurstart + 103] + i;
              }

              /* end de la comprobaci�n de si el nodo expandido tiene un coste menor con el nuevo padre */
              /* '<S1>:1:217' */
              trayecTHETALstaresc_sizes_idx = 1;
            }

            /* end de la comprobaci�n de si el nodo estaba en la lista abierta */
          }

          /* end del recuento para todos los nodos de la lista abierta */
          if (trayecTHETALstaresc_sizes_idx == 0) {
            /* '<S1>:1:222' */
            /* '<S1>:1:223' */
            open_cont++;

            /* '<S1>:1:224' */
            trayecTHETALstaresc_sizes_idx = (int32_T)open_cont - 1;
            codigoc_B.open[trayecTHETALstaresc_sizes_idx] = 1.0;
            codigoc_B.open[trayecTHETALstaresc_sizes_idx + 200000] = nodos_exp
              [(int32_T)heurstart - 1];
            codigoc_B.open[trayecTHETALstaresc_sizes_idx + 400000] = nodos_exp
              [(int32_T)heurstart + 25];
            codigoc_B.open[trayecTHETALstaresc_sizes_idx + 600000] = nodos_exp
              [(int32_T)heurstart + 51];
            codigoc_B.open[trayecTHETALstaresc_sizes_idx + 800000] = nodopadre[0];
            codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1000000] = nodopadre
              [1];
            codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1200000] = nodopadre
              [2];
            codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1400000] = i;
            codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1600000] = nodos_exp
              [(int32_T)heurstart + 103];
            codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1800000] = nodos_exp
              [(int32_T)heurstart + 103] + i;
          }
        }
      }

      /* '<S1>:1:231' */
      iter++;

      /* se actualiza el numero de iteraciones */
    } else {
      /* '<S1>:1:153' */
      NoSol = 1;

      /* Si no hay nodos disponibles en la lista abierta, no habr� soluci�n */
      exitg = TRUE;
    }
  }

  /* '<S1>:1:235' */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* % Fin del algoritmo ==> CALCULO DE LA TRAYECTORIA %% */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* El algoritmo ya ha terminado. Ahora habr� que determinar la trayectoria */
  /* �ptima empezando en el �ltimo nodo (que debiera ser el destino) e ir */
  /* identificando sus padres hasta llegar al nodo de origen. */
  /* Determinar el padre del nodo y sus sucesivos padres hasta llegar al origen */
  /* El n�mero 1000 significar� que como mucho podremos procesar un camino de */
  /* 1000 puntos. */
  /* '<S1>:1:250' */
  /* '<S1>:1:251' */
  for (i_0 = 0; i_0 < 3000; i_0++) {
    codigoc_B.trayectoriaesc[i_0] = 0.0;
    codigoc_B.trayecTHETALstar[i_0] = 0.0;
  }

  if (NoSol == 0) {
    /* '<S1>:1:253' */
    /* '<S1>:1:256' */
    /* '<S1>:1:259' */
    trayecTHETALstaresc_sizes_idx = (int32_T)closed_cont - 1;
    codigoc_B.trayectoriaesc[0] = codigoc_B.closed[trayecTHETALstaresc_sizes_idx];
    codigoc_B.trayectoriaesc[1000] =
      codigoc_B.closed[trayecTHETALstaresc_sizes_idx + 200000];
    codigoc_B.trayectoriaesc[2000] =
      codigoc_B.closed[trayecTHETALstaresc_sizes_idx + 400000];

    /* '<S1>:1:260' */
    i = 2.0;
    if ((codigoc_B.closed[(int32_T)closed_cont - 1] == xfin) &&
        (codigoc_B.closed[(int32_T)closed_cont + 199999] == yfin) &&
        (codigoc_B.closed[(int32_T)closed_cont + 399999] == hfin)) {
      /* '<S1>:1:262' */
      /* '<S1>:1:263' */
      trayecTHETALstaresc_sizes_idx = (int32_T)closed_cont - 1;
      closed[0] = codigoc_B.closed[trayecTHETALstaresc_sizes_idx];
      closed[1] = codigoc_B.closed[trayecTHETALstaresc_sizes_idx + 200000];
      closed[2] = codigoc_B.closed[trayecTHETALstaresc_sizes_idx + 400000];
      trayecTHETALstaresc_sizes_idx = (int32_T)codigoc_indice(&codigoc_B.open[0],
        closed, open_cont) - 1;
      nodopadre[0] = codigoc_B.open[trayecTHETALstaresc_sizes_idx + 800000];
      nodopadre[1] = codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1000000];
      nodopadre[2] = codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1200000];

      /* Coordenadas del padre del nodo elegido */
      while ((nodopadre[0] != xini) || (nodopadre[1] != yini) || (nodopadre[2]
              != hini)) {
        /* '<S1>:1:265' */
        /* '<S1>:1:266' */
        i_0 = (int32_T)i - 1;
        codigoc_B.trayectoriaesc[i_0] = nodopadre[0];
        codigoc_B.trayectoriaesc[i_0 + 1000] = nodopadre[1];
        codigoc_B.trayectoriaesc[i_0 + 2000] = nodopadre[2];

        /* Obtenemos el indice del padre del padre */
        /* '<S1>:1:268' */
        /* '<S1>:1:269' */
        trayecTHETALstaresc_sizes_idx = (int32_T)codigoc_indice(&codigoc_B.open
          [0], nodopadre, open_cont) - 1;
        nodopadre[0] = codigoc_B.open[trayecTHETALstaresc_sizes_idx + 800000];
        nodopadre[1] = codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1000000];
        nodopadre[2] = codigoc_B.open[trayecTHETALstaresc_sizes_idx + 1200000];

        /* '<S1>:1:270' */
        i++;
      }

      /* '<S1>:1:272' */
      i_0 = (int32_T)i - 1;
      codigoc_B.trayectoriaesc[i_0] = xini;
      codigoc_B.trayectoriaesc[i_0 + 1000] = yini;
      codigoc_B.trayectoriaesc[i_0 + 2000] = hini;
    }

    /* Ahora ordeno la trayectoria para tenerla desde el punto inicial al punto */
    /* final */
    /* k=size(trayectoriaesc,1);  */
    /* '<S1>:1:278' */
    k = i;

    /* '<S1>:1:279' */
    /* '<S1>:1:280' */
    trayecTHETALstaresc_sizes_idx = (int32_T)i;
    loop_ub = (int32_T)i * 3 - 1;
    for (i_0 = 0; i_0 <= loop_ub; i_0++) {
      codigoc_B.trayecTHETALstaresc_data[i_0] = 0.0;
    }

    for (heurstart = 1.0; heurstart <= i; heurstart++) {
      /* '<S1>:1:282' */
      /* '<S1>:1:283' */
      loop_ub = (int32_T)heurstart - 1;
      k_0 = (int32_T)k - 1;
      codigoc_B.trayecTHETALstaresc_data[loop_ub] = codigoc_B.trayectoriaesc[k_0];
      codigoc_B.trayecTHETALstaresc_data[loop_ub + trayecTHETALstaresc_sizes_idx]
        = codigoc_B.trayectoriaesc[k_0 + 1000];
      codigoc_B.trayecTHETALstaresc_data[loop_ub +
        (trayecTHETALstaresc_sizes_idx << 1)] = codigoc_B.trayectoriaesc[k_0 +
        2000];

      /* '<S1>:1:284' */
      k--;
    }

    /* Des-escalado de los waypoints de la trayectoria */
    /* '<S1>:1:289' */
    heurstart = ext1_idx - ext0_idx;
    k = codigoc_U.n[0] * ext0_idx;
    ind_parent = codigoc_U.n[0] - 1.0;

    /* '<S1>:1:290' */
    loop_ub = trayecTHETALstaresc_sizes_idx - 1;
    for (i_0 = 0; i_0 <= loop_ub; i_0++) {
      codigoc_B.trayecTHETALstar[i_0] = (heurstart *
        codigoc_B.trayecTHETALstaresc_data[i_0] - (ext1_idx - k)) / ind_parent;
    }

    /* '<S1>:1:289' */
    heurstart = ext1_idx_0 - ext0_idx_0;
    k = codigoc_U.n[1] * ext0_idx_0;
    ind_parent = codigoc_U.n[1] - 1.0;

    /* '<S1>:1:290' */
    loop_ub = trayecTHETALstaresc_sizes_idx - 1;
    for (i_0 = 0; i_0 <= loop_ub; i_0++) {
      codigoc_B.trayecTHETALstar[i_0 + 1000] =
        (codigoc_B.trayecTHETALstaresc_data[i_0 + trayecTHETALstaresc_sizes_idx]
         * heurstart - (ext1_idx_0 - k)) / ind_parent;
    }

    /* '<S1>:1:289' */
    heurstart = ext1_idx_1 - ext0_idx_1;
    k = codigoc_U.n[2] * ext0_idx_1;
    ind_parent = codigoc_U.n[2] - 1.0;

    /* '<S1>:1:290' */
    loop_ub = trayecTHETALstaresc_sizes_idx - 1;
    for (i_0 = 0; i_0 <= loop_ub; i_0++) {
      codigoc_B.trayecTHETALstar[i_0 + 2000] =
        (codigoc_B.trayecTHETALstaresc_data[(trayecTHETALstaresc_sizes_idx << 1)
         + i_0] * heurstart - (ext1_idx_1 - k)) / ind_parent;
    }
  }

  /* timeTHETALstar=cputime-time; %tiempo empleado en calcular la trayectoria */

  /* Outport: '<Root>/trayecTHETALstar' */
  memcpy((void *)(&codigoc_Y.trayecTHETALstar[0]), (void *)
         (&codigoc_B.trayecTHETALstar[0]), 3000U * sizeof(real_T));

  /* Outport: '<Root>/linechecks' */
  codigoc_Y.linechecks = iter;
}

/* Model initialize function */
void codigocModelClass::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(codigoc_M, (NULL));

  /* external inputs */
  (void) memset((void *)&codigoc_U, 0,
                sizeof(ExternalInputs_codigoc));

  /* external outputs */
  (void) memset((void *)&codigoc_Y, 0,
                sizeof(ExternalOutputs_codigoc));
}

/* Model terminate function */
void codigocModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
codigocModelClass::codigocModelClass()
{
  /* Real-Time Model */
  codigoc_M = &codigoc_M_;
}

/* Destructor */
codigocModelClass::~codigocModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_codigoc * codigocModelClass::getRTM() const
{
  return codigoc_M;
}

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
