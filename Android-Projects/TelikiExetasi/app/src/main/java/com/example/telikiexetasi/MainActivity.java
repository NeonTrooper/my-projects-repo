package com.example.telikiexetasi;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView textViewMatrix = findViewById(R.id.textViewMatrix);
        TextView textViewResult = findViewById(R.id.textViewResult);

        // Δημιουργία πίνακα 3x3
        int[][] matrix = new int[3][3];

        // Αρχικοποίηση του πίνακα με τυχαίες ακέραιες τιμές από 0 έως 100
        Random random = new Random();
        StringBuilder matrixText = new StringBuilder("Ο πίνακας είναι:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrix[i][j] = random.nextInt(101); // Τυχαίος αριθμός από 0 έως 100
                matrixText.append(matrix[i][j]).append("\t");
            }
            matrixText.append("\n");
        }

        // Εμφάνιση του πίνακα στο TextView
        textViewMatrix.setText(matrixText.toString());

        // Υπολογισμός και εμφάνιση του άθροισματος των στοιχείων του πίνακα
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                sum += matrix[i][j];
            }
        }
        textViewResult.setText("Άθροισμα στοιχείων: " + sum);
    }
}
