package com.example.lab1ballscollision;

import com.example.lab1ballscollision.objects.Vector;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class VectorUnitTests {
    @Test
    public void addition_isCorrect() {
        Vector a = new Vector(1.0, 0.0, 1.0), b = new Vector(0.0, 1.0, 0.0), c = a.add(b);
        if (Math.abs(c.x - 1.0) >= 0.01) fail();
        if (Math.abs(c.y - 1.0) >= 0.01) fail();
        if (Math.abs(c.z - 1.0) >= 0.01) fail();
    }

    @Test
    public void subtraction_isCorrect() {
        Vector a = new Vector(1.0, 0.0, 1.0), b = new Vector(0.0, 1.0, 0.0), c = a.subtract(b);
        if (Math.abs(c.x - 1.0) >= 0.01) fail();
        if (Math.abs(c.y + 1.0) >= 0.01) fail();
        if (Math.abs(c.z - 1.0) >= 0.01) fail();
    }

    @Test
    public void normalisation_isCorrect() {
        Vector a = new Vector(10.0, 5.3, 1.0);
        if (Math.abs(a.normalise().length() - 1.0) >= 0.01) fail();
    }

    @Test
    public void length_isCorrect() {
        Vector a = new Vector(1.0,1.0,1.0);
        if (Math.abs(a.length() - Math.sqrt(3.0)) >= 0.01) fail();
    }

    @Test
    public void multOnScalar_isCorrect() {
        Vector a = new Vector(1.0,2.0,3.0), b = a.multOnScalar(2);
        if (Math.abs(b.x - 2.0) >= 0.01) fail();
        if (Math.abs(b.y - 4.0) >= 0.01) fail();
        if (Math.abs(b.z - 6.0) >= 0.01) fail();
    }

    @Test
    public void scalarCompos_isCorrect() {
        Vector a = new Vector(1.0,2.0,0.0), b = new Vector(-3.0, 3.0, 1.0);
        if (Math.abs(a.scalarCompos(b) - 3.0) >= 0.01) fail();
    }

    @Test
    public void vectorCompos_isCorrect() {
        Vector a = new Vector(1.0,2.0,3.0), b = a.multOnScalar(2), c = a.vectorCompos(b);
        if (Math.abs(c.x) >= 0.01) fail();
        if (Math.abs(c.y) >= 0.01) fail();
        if (Math.abs(c.z) >= 0.01) fail();
    }

}