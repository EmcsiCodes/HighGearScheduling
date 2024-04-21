import numpy as np
import pandas as pd
from math import radians

def haversine(lon1, lat1, lon2, lat2):
    """
    Calculate the great circle distance in kilometers between two points 
    on the earth (specified in decimal degrees).
    """
    # Convert decimal degrees to radians
    lon1, lat1, lon2, lat2 = map(radians, [lon1, lat1, lon2, lat2])

    # Haversine formula
    dlon = lon2 - lon1
    dlat = lat2 - lat1
    a = np.sin(dlat / 2) ** 2 + np.cos(lat1) * np.cos(lat2) * np.sin(dlon / 2) ** 2
    c = 2 * np.arcsin(np.sqrt(a))

    # 6371 km is the radius of the Earth
    km = 6371 * c
    return km

def distance_matrix(coords):
    """
    Create a distance matrix for the given list of coordinates, where each coordinate is a tuple (longitude, latitude).
    """
    num_points = len(coords)
    dist_matrix = np.zeros((num_points, num_points))

    for i in range(num_points):
        for j in range(i + 1, num_points):
            dist = haversine(coords[i][0], coords[i][1], coords[j][0], coords[j][1])
            dist_matrix[i, j] = dist_matrix[j, i] = dist

    return dist_matrix

def read_coordinates(in_file_path):
    """
    Reads a CSV file with longitude and latitude values and returns a list of tuples.
    """
    df = pd.read_csv(in_file_path, usecols=[3, 4], header=None, names=['longitude', 'latitude'])
    return [(float(row['longitude']), float(row['latitude'])) for index, row in df.iterrows()]

# Example usage
in_file_path = 'hackmk.csv'  # Replace with your file path
out_file_path = 'distanceMatrix.txt'

def save_distance_matrix(matrix, file_path):
    """
    Save the distance matrix to a text file separated by space.
    """
    np.savetxt(file_path, matrix, fmt='%0.2f', delimiter=' ')

coords = read_coordinates(in_file_path)
matrix = distance_matrix(coords)
save_distance_matrix(matrix,out_file_path);