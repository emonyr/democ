#ifndef GPIO_H
#define GPIO_H

struct s5p_gpio_bank {
	unsigned int	con;
	unsigned int	dat;
	unsigned int	pull;
	unsigned int	drv;
	unsigned int	pdn_con;
	unsigned int	pdn_pull;
	unsigned char	res1[8];
};

struct s5p_gpio{
	struct s5p_gpio_bank gpa0;
	struct s5p_gpio_bank gpa1;
	struct s5p_gpio_bank gpb;
	struct s5p_gpio_bank gpc0;
	struct s5p_gpio_bank gpc1;
	struct s5p_gpio_bank gpd0;
	struct s5p_gpio_bank gpd1;
	struct s5p_gpio_bank gpe0;
	struct s5p_gpio_bank gpe1;
	struct s5p_gpio_bank gpf0;
	struct s5p_gpio_bank gpf1;
	struct s5p_gpio_bank gpf2;
	struct s5p_gpio_bank gpf3;
	struct s5p_gpio_bank gpg0;
	struct s5p_gpio_bank gpg1;
	struct s5p_gpio_bank gpg2;
	struct s5p_gpio_bank gpg3;
	struct s5p_gpio_bank gpi;
	struct s5p_gpio_bank gpj0;
	struct s5p_gpio_bank gpj1;
	struct s5p_gpio_bank gpj2;
	struct s5p_gpio_bank gpj3;
	struct s5p_gpio_bank gpj4;
};




#endif
