
'''
Creating the class Toll_Cost() makes each functions work more collectively rather than having a
group of static functions
'''
class Toll_Cost:

    zone = 0 #Global variable to hold zone marker

    #To display instructions
    def display_instructions(self):

        print(
            "This program calculates the toll charges for a paid highway."
            "\nLight vehicles will be charged at a rate of 40.85 cents per km."
            "\nHeavyvehicles will be charged at a rate of 81.75 cents per km."
            "\n There are three travelling zones as follow:"
            "\n\t-Zone 1: from km marker 0 to marker 30."
            "\n\t-Zone 2: from km marker 31 to marker 60. "
            "\n\t-Zone 3: from km marker 61 to marker 90."
            "\nThere will be a surcharge of 27% to travel in Zone 2."
            "\nEach trip will be charged a highway entrance fee of $1.25."
            "\nVehicles without a rental transponder will be charged an additional"
            "\ncamera recording fee of $4.15."
            "\nAll applicable Ontario taxes (13%) will be added to the total.")
        return


    def calculate_toll_charge(self, entry, exit, vehicle):

        entrance = 125 #in cents for easy conversion
        light_rate_charge = 40.85
        heavy_rate_charge = 81.75
        rate_to_charge = 0

        entry_marker = int(entry)
        exit_marker = int(exit)

        determine_entry= self.determine_zone(entry_marker)
        determine_exit = self.determine_zone(exit_marker)

        '''
        To know the rate to use, right away
        '''
        if (vehicle.upper() == "H"):
            rate_to_charge = heavy_rate_charge
        elif (vehicle.upper() == "L"):
            rate_to_charge = light_rate_charge

        distance = int(exit) - int(entry)

        if distance < 0:
            distance = -distance # so that distance remains positive
        '''
        Major cases to consider: 
        -Vehicle is driven in zone 2 only, the else statement takes care of 1 only & 3 only
        -Vehicle enters from 1 and exits at 2. Vehicle enters from 2 and exits at 1
        -Vehicle enters from 2 en exits at  3. Vehicle enters from 3 and exits at 2
        -Vehicle enters from 3 and exits at 1. Vehicle enters from 1 and exits at 3
        -With entry and exits between zones 1-3 solely, the distance in zone 2 is always going to be 30km
        '''
        if determine_entry == 2 and determine_exit == 2:

            distance = entry_marker - exit_marker

            if distance < 0:
                distance = -distance # so that distance remains positive again for this case

            charge = (distance*rate_to_charge) + entrance + (0.27*(distance*rate_to_charge))

        elif determine_entry == 1 and determine_exit == 2:

            zone2_distance = exit_marker - 30

            charge = (distance*rate_to_charge) + (zone2_distance * rate_to_charge)*0.27 +entrance

        elif determine_entry == 2 and determine_exit == 1:

            zone2_distance = entry_marker - 30
            charge = (distance * rate_to_charge) + (zone2_distance * rate_to_charge)*0.27 + entrance

        elif determine_entry == 2 and determine_exit == 3:

            zone2_distance = 60 - entry_marker
            charge = (distance * rate_to_charge) + (zone2_distance * rate_to_charge) * 0.27 + entrance

        elif determine_entry == 3 and determine_exit == 2:

            zone2_distance = 60 - exit_marker
            charge = (distance * rate_to_charge) + (zone2_distance * rate_to_charge) * 0.27 + entrance

        elif (determine_entry == 1 and determine_exit == 3) or (determine_exit == 1 and determine_entry == 3):

            zone2_distance = 30
            charge = (distance*rate_to_charge)+ (zone2_distance*rate_to_charge) * 0.27 + entrance
        else:
            charge = (distance * rate_to_charge) + entrance

        return charge

    '''
    Returns respective zone when given a marker
    '''
    def determine_zone(self, marker):

        if marker <= 30:
            self.zone = 1
        elif marker > 30  and marker <= 60:
            self.zone = 2
        elif marker > 61 and marker <=90:
            self.zone = 3

        return self.zone

    '''
    Return total bill which can be affected by absence of transponder
    '''
    def calculate_total_bill(self, trip, transponder):

        no_transponder_fee = 415 #in cents
        total_bill = trip + (0.13 * trip)

        if transponder.upper() == "N":
            temp_bill = trip + no_transponder_fee
            total_bill = temp_bill + (0.13 * temp_bill)
            print("NOTE: Since you do not own a transponder, you will be required to pay "
                  "an additional camera recording fee of $4.15.")
        print("Total due is: $", round(total_bill/100, 2))

        return total_bill

'''
To run the Class
'''
if __name__ == '__main__':

    Toll_Cost().display_instructions()

    input_entry = input("Enter the entry marker: ")
    input_exit = input("Enter the exit marker:  ")
    input_vehicle = input("Enter your vehicle type (L)ight or (H)eavy: ")
    input_transponder = input("Do you have a transponder (Y)es or (N)o: ")

    trip = Toll_Cost().calculate_toll_charge(input_entry, input_exit, input_vehicle)
    Toll_Cost().calculate_total_bill(trip, input_transponder)