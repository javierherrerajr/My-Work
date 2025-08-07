import { render, screen } from '@testing-library/react';
import { ReviewButton } from '../ReviewButton';

describe('ReviewButton', () => {
  it('renders button with correct text', () => {
    render(<ReviewButton courseId="CS100" />);
    expect(screen.getByText('Submit a Review')).toBeInTheDocument();
  });

  it('renders link with correct href', () => {
    render(<ReviewButton courseId="CS100" />);
    
    const link = screen.getByRole('link');
    expect(link).toHaveAttribute('href', '/review?courseId=CS100');
  });

  it('applies correct styling classes', () => {
    render(<ReviewButton courseId="CS100" />);
    
    const button = screen.getByRole('link').querySelector('button');
    expect(button).toHaveClass(
      '!bg-[#B0C69A]',
      'hover:!bg-[#9DB68A]',
      'font-poppins',
      'font-semibold',
      '!text-[#2C1818]',
      'text-[14px]',
      'md:text-[18px]',
      'w-[200px]',
      'mb-3'
    );
  });

  it('handles different course IDs', () => {
    render(<ReviewButton courseId="EE101" />);
    
    const link = screen.getByRole('link');
    expect(link).toHaveAttribute('href', '/review?courseId=EE101');
  });
}); 