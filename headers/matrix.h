#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <vector>

/**
 * \class {matrix}
 * \brief {classe qui permet de manipuler des matrices}
 * 
 */
class Matrix {

    private:
        int rows_, cols_; /*dimensions de la matrice*/
        double **p; /*pointeur vers le tableau de données*/

        void allocSpace(); /*allocation de l'espace mémoire*/


    public:

        /**
        *\brief Constructeur de la classe Matrix
        * \param int : nombre de lignes de la matrice
        * \param int : nombre de colonnes de la matrice
        */

        Matrix(int, int);

        /*!
        *\brief Constructeur de la classe Matrix
        */
        Matrix() : rows_(0), cols_(0), p() {};

        /**
        *\brief Destructeur de la classe Matrix
        */
        ~Matrix();

        /**
        *\brief Constructeur de copie de la classe Matrix
        * \param Matrix : matrice à copier
        */

        Matrix(const Matrix&);

        /**
         * \brief Opérateur d'affectation de la classe Matrix
         * \param Matrix : matrice à assigner
         * \return Matrix& : référence vers la matrice assignée
         */

        Matrix& operator=(const Matrix&);

        /**
         * \brief Surcharge de l'opérateur () pour accéder aux éléments de la matrice
         * \param int : indice de la ligne
         * \param int : indice de la colonne
         * \return double& : référence vers l'élément de la matrice
         */

        inline double& operator()(int x, int y) { return p[x][y]; }

        /**
         * \brief Surcharge de l'opérateur () pour accéder aux éléments de la matrice
         * \param int : indice de la ligne
         * \return double& : référence vers l'élément de la matrice
         */

        inline double operator()(int x) { return p[x][0]; }

        /**
         * \brief Surcharge de l'opérateur d'accès aux éléments de la matrice (version constante).
         *
         * \param x : indice de ligne
         * \param y : indice de colonne
         * \return double : valeur de l'élément de la matrice
         */

        inline double operator()(int x, int y) const { return p[x][y]; }

        
        /**
         * \brief Surcharge de l'opérateur -= pour soustraire une matrice à une autre
         * \param Matrix : matrice à soustraire
         * \return Matrix& : référence vers la matrice résultat
         */
        Matrix& operator-=(const Matrix&);

        /**
         * \brief Surcharge de l'opérateur *= pour multiplier une matrice par une autre
         * \param Matrix : matrice à multiplier
         * \return Matrix& : référence vers la matrice résultat
         */
        Matrix& operator*=(const Matrix&);

        /**
         * \brief Surcharge de l'opérateur *= pour multiplier une matrice par un scalaire
         * \param double : scalaire à multiplier
         * \return Matrix& : référence vers la matrice résultat
         */
        Matrix& operator*=(double);

        /**
         * \brief Surcharge de l'opérateur /= pour diviser une matrice par un scalaire
         * \param double : scalaire à diviser
         * \return Matrix& : référence vers la matrice résultat
         */
        Matrix& operator/=(double);
        

        /**
         * \brief Surcharge de l'opérateur << pour afficher une matrice
         * \param std::ostream& : flux de sortie
         * \param Matrix : matrice à afficher
         * \return std::ostream& : flux de sortie
        */
        friend std::ostream& operator<<(std::ostream&, const Matrix&);

        /**
         * \brief Permet d'echanger deux lignes de la matrice
         * \param int : indice de la première ligne
         * \param int : indice de la deuxième ligne
         * \return void
        */
        void swapRows(int, int);

        /**
         * \brief Permet de transposer la matrice
         * \return Matrix : matrice transposée
        */
        Matrix transpose();

        /**
         * \brief Permet de redimensionner la matrice
         * \param int : nombre de lignes de la nouvelle matrice
         * \param int : nombre de colonnes de la nouvelle matrice
         * \return Matrix : matrice redimensionnée
        */
        Matrix reshape(int newRows, int newCols) const;

        /**
         * \brief Permet de créer une matrice identité
         * \param int : dimension de la matrice identité
         * \return Matrix : matrice identité
        */
        static Matrix createIdentity(int);

        /**
         * \brief Permet de résoudre un système d'équations linéaires de la forme Ax = b
         * ce sera utile pour implémenter la méthode inverse()
         * \param Matrix : matrice des coefficients du système
         * \param Matrix : matrice des resultats du système
         * \return Matrix : matrice des solutions du système
        */
        static Matrix solve(Matrix, Matrix);


        /**
         * \brief Permet d'augmenter une matrice ce qui veut dire de concaténer deux matrices
         * \param Matrix : matrice à augmenter
         * \param Matrix : matrice à concaténer
         * \return Matrix : matrice augmentée
        */
        static Matrix augment(Matrix, Matrix);

        /**
         * \brief Effectue l'élimination de Gauss sur une matrice.
         *
         * Cette fonction applique l'élimination de Gauss pour transformer une matrice
         * en sa forme échelonnée réduite.
         *
         * \return La forme échelonnée réduite de la matrice après l'élimination de Gauss.
         */
        Matrix gaussianEliminate();


        /**
         * \brief Permet de réduire une matrice à sa forme échelonnée réduite
         * \return Matrix : matrice réduite
        */
        Matrix rowReduceFromGaussian();

        /**
         * \brief Permet de calculer l'inverse d'une matrice
         * \return Matrix : matrice inverse
        */
        Matrix inverse() const;

        /**
         * \return Renvoie le nombre de lignes d'une matrice
        */
        int rows() const {return rows_;}

        /**
         * \return Renvoie le nombre de colonnes d'une matrice
        */
        int cols() const {return cols_;}


        /**
         * \brief Permet de récupérer une ligne de la matrice
         * \param int : indice de la ligne
         * \return std::vector<double> : ligne de la matrice
        */
        const std::vector<double> getRow(int row) const;

        /**
         * \brief Permet de récupérer la valeur maximale de la matrice
         * \param Matrix : matrice 
         * \return double : valeur maximale de la matrice
        */
        double max() const;

        /**
         * \brief Permet de récupérer la valeur maximale dans un vecteur de matrice
         * \param std::vector<Matrix> : vecteur de matrice
         * \return double : valeur maximale dans le vecteur de matrice
        */
        static double max(const std::vector<Matrix>&);

};

/**
 * \brief Surcharge de l'opérateur de soustraction entre deux matrices.
 * \param m1 : Première matrice.
 * \param m2 : Deuxième matrice.
 * \return Matrix : Résultat de la soustraction (m1 - m2).
 */
Matrix operator-(const Matrix& m1, const Matrix& m2);

/**
 * \brief Surcharge de l'opérateur de multiplication entre deux matrices.
 * \param m1 : Première matrice.
 * \param m2 : Deuxième matrice.
 * \return Matrix : Résultat de la multiplication (m1 * m2).
 */
Matrix operator*(const Matrix& m1, const Matrix& m2);

/**
 * \brief Surcharge de l'opérateur de multiplication entre une matrice et un scalaire.
 *
 * \param m : Matrice.
 * \param scalar : Scalaire.
 * \return Matrix : Résultat de la multiplication (m * scalar).
 */
Matrix operator*(const Matrix& m, double scalar);

/**
 * \brief Surcharge de l'opérateur de multiplication entre un scalaire et une matrice.
 * \param scalar : Scalaire.
 * \param m : Matrice.
 * \return Matrix : Résultat de la multiplication (scalar * m).
 */
Matrix operator*(double scalar, const Matrix& m);

/**
 * \brief Surcharge de l'opérateur de division entre une matrice et un scalaire.
 * \param m : Matrice.
 * \param scalar : Scalaire.
 * \return Matrix : Résultat de la division (m / scalar).
 */
Matrix operator/(const Matrix& m, double scalar);

#endif