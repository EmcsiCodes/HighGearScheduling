import csv

# Open the CSV file
with open('test.csv', 'r') as file:
    # Create a CSV reader object
    reader = csv.reader(file)
    
    # Open a new file to write the extracted values
    with open('output.txt', 'w') as output_file:
        # Iterate over each row in the CSV file
        for row in reader:
            # Check if the row has at least 6 elements
            if len(row) >= 6:
                # Extract the fifth and sixth values from the row
                fifth_value = row[3]
                sixth_value = row[4]
                
                # Write the fifth and sixth values to the output file
                output_file.write(f"{fifth_value} {sixth_value}\n")
            else:
                output_file.write("Row does not have enough elements\n")
