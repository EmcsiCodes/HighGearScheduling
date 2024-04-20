import csv
from math import sin, cos, sqrt, atan2, radians

# Read coordinates from output.txt
coordinates = []
R = 6373.0

with open('output.txt', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        # Split each row by space and append the resulting list to coordinates
        coordinates.append(row[0].split())

with open('output2.txt', 'w') as output_file:
    # Iterate over each pair of coordinates
    for i in range(len(coordinates)):
        origin_lat, origin_lng = map(float, coordinates[i])
        row_distances = []

        # Start inner loop from index i+1 to avoid redundant comparisons
        for j in range(i, len(coordinates)):
            dest_lat, dest_lng = map(float, coordinates[j])
            print(f"i={i}, j={j}")

            # Convert latitude and longitude to radians
            origin_lat_rad = radians(origin_lat)
            origin_lng_rad = radians(origin_lng)
            dest_lat_rad = radians(dest_lat)
            dest_lng_rad = radians(dest_lng)

            # Calculate distance from origin to destination
            dlon = dest_lng_rad - origin_lng_rad
            dlat = dest_lat_rad - origin_lat_rad
            a = sin(dlat/2)**2 + cos(origin_lat_rad) * cos(dest_lat_rad) * sin(dlon/2)**2
            c = 2 * atan2(sqrt(a), sqrt(1-a))
            distance = R * c

            # Append distance to row_distances list, formatted with 2 decimal digits
            row_distances.append("{:.2f}".format(distance))

        # Write row_distances list to output2.txt
        output_file.write(' '.join(row_distances) + '\n')

print("Distance matrix written to output2.txt")
