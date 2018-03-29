import unittest
import numpy as np
import sys

sys.path.insert(0, "@PYTHON_MODULE_PATH@")

import higra as hg


def compare(t1, t2):
    if len(t1) != len(t2):
        return False
    for i in range(len(t1)):
        if t1[i] != t2[i]:
            return False
    return True


class TestEmbedding(unittest.TestCase):

    def test_createEmbedding(self):
        e1 = hg.EmbeddingGrid((3, 5, 2))
        e2 = hg.EmbeddingGrid([3, 5, 2])
        e3 = hg.EmbeddingGrid(np.asarray([3, 5, 2], dtype=np.int64))

        for e in (e1, e2, e3):
            self.assertTrue(e.dimension() == 3)
            self.assertTrue(e.size() == 30)
            self.assertTrue(compare(e.shape(), (3, 5, 2)))

    def test_contains(self):
        e1 = hg.EmbeddingGrid((3, 5, 2))
        self.assertTrue(e1.contains((1, 3, 1)))
        self.assertTrue(e1.contains((0, 0, 0)))
        self.assertTrue(e1.contains((2, 4, 1)))
        self.assertFalse(e1.contains((-1, 4, 1)))
        self.assertFalse(e1.contains((2, 4, 2)))

    def test_containsV(self):
        e1 = hg.EmbeddingGrid((5, 10))
        coords = np.asarray((((0, 0), (3, 8), (-1, 2)),
                             ((2, 4), (5, 5), (43, 44))), dtype=np.int64)

        ref = np.asarray(((True, True, False),
                          (True, False, False)))

        res = e1.contains(coords)

        self.assertTrue(np.array_equal(ref, res))


if __name__ == '__main__':
    unittest.main()